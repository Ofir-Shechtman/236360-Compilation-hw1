#!/usr/bin/python3.6
import subprocess
import os
import shutil
import re
from optparse import OptionParser

#globals
tempDirName = "tmp_test_xyz_dir"
done = "Done!"
scannerFile = "scanner.lex"
partAFile = "part_a.cpp"
tokensFile = "tokens.hpp"
failedTestsDirName = "failedTests"
testsTaken = 0
testsFailed = 0

def natural_sort(l): 
    convert = lambda text: int(text) if text.isdigit() else text.lower() 
    alphanum_key = lambda key: [ convert(c) for c in re.split('([0-9]+)', key) ] 
    return sorted(l, key = alphanum_key)

def exitIfsubprocessError(err):
    if err:        
        decoded_error = err.decode('ascii')        
        raise ValueError(decoded_error)                
        
def padText(text, totalLength, character):
    if totalLength <= len(text) + 2:
        return text
    paddingLength = totalLength - len(text) - 2
    extraSpace = " " if paddingLength % 2 == 1 else ""
    return character + " " * (int(paddingLength / 2)) + text + " " * (int(paddingLength / 2)) + extraSpace + character

def printHeadline(text):
    delimiter = "--------------------------------------------------------------------------"
    print(delimiter)
    print(padText(text, len(delimiter), '|'))
    print(delimiter)
    
def runCommand(cmd):
    (output, err) = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE).communicate()
    exitIfsubprocessError(err)
    print(done)

def createTmpWorkArea():
    printHeadline("Creating tmp workspace")
    if os.path.isdir(tempDirName):
        if options['allowDelete']:
            shutil.rmtree(tempDirName)
            os.mkdir(tempDirName)
    else:
        os.mkdir(tempDirName)        
    print(done)

def copyCompilationFiles():
    printHeadline("Copying files")
    if not os.path.isfile(scannerFile):        
        raise ValueError("No scanner.lex file.")        
    if not os.path.isfile(partAFile):        
        raise ValueError("No part_a.cpp file.")        
    if not os.path.isfile(tokensFile):        
        raise ValueError("No tokens.hpp file.")
    shutil.copyfile(scannerFile, os.path.join(tempDirName, scannerFile))
    shutil.copyfile(partAFile, os.path.join(tempDirName, partAFile))
    shutil.copyfile(tokensFile, os.path.join(tempDirName, tokensFile))
    print('Done!')

def cleanExit():
    if options['allowDelete']:
        printHeadline("Cleaning work area")
        if os.path.isdir(tempDirName):                         
            shutil.rmtree(tempDirName)    
        print('Done!')
    exit(0)

def compareResults(expected, actual):
    global testsFailed
    if not expected == actual:
        testsFailed += 1
        return False
    else:
        return True

def processFailedTest(pathIn, pathOut, output):
    if not os.path.isdir(failedTestsDirName):
        os.mkdir(failedTestsDirName)    
    name = re.search(r'([\w\.\/]+).in$', pathIn)         
    if not name or not name.groups() or not name.groups()[0]:
            print(f"trouble proccessing file {inFilePath}")
            return
    name = os.path.basename(name.groups()[0])    
    testDirPath = os.path.join(failedTestsDirName, name)    
    if not os.path.isdir(testDirPath):
        os.mkdir(testDirPath)        
    shutil.copyfile(pathIn, os.path.join(testDirPath, os.path.basename(pathIn)))
    shutil.copyfile(pathOut, os.path.join(testDirPath, os.path.basename(pathOut)))
    outputFileName = os.path.join(testDirPath, name + '.testout')    
    with open(outputFileName, 'w') as outputFile:
        outputFile.write(output)    
    print("Expected :")
    print("*********************************")
    with open(pathOut, 'r') as outFileFd:
        print(outFileFd.read(), end='')
    print("*********************************")
    print("Got :")    
    print("*********************************")
    print(output, end='')
    print("*********************************")            

def runTest(pathIn, pathOut):
    with open(pathIn, 'r') as inFile, open(pathOut, 'r') as expectedOutputFile:        
        global testsTaken
        cmd = [os.path.join(tempDirName, 'tmptmptmp')]
        (output, err) = subprocess.Popen(cmd, stdin=inFile, stdout=subprocess.PIPE, stderr=subprocess.PIPE).communicate()
        testsTaken += 1
        return [compareResults(output.decode('unicode_escape'), expectedOutputFile.read()), output.decode('unicode_escape')]

def runTests():
    files = [f for f in os.listdir('tests') if os.path.isfile(os.path.join('tests', f))]
    inFiles = natural_sort([f for f in files if re.search(r'\.in$', f)])
    outFiles = natural_sort([f for f in files if re.search(r'\.out$', f)])    
    for file in inFiles:        
        inFilePath = os.path.join('tests', file)                
        name = re.search(r'([\w\.\/]+).in$', inFilePath)                        
        if not name or not name.groups() or not name.groups()[0]:
            print(f"trouble proccessing file {inFilePath}")
        outFilePath = name.groups()[0] + ".out"                
        if not os.path.isfile(outFilePath):
            print(f"there is no out file for {inFilePath}, skipping...")                        
            continue
        result, output = runTest(inFilePath, outFilePath)
        baseTestName = os.path.basename(name.groups()[0])
        if not result:
            print(f"{baseTestName}: FAILED")
            processFailedTest(inFilePath, outFilePath, output)
        else:
            print(f"{baseTestName}: PASSED")

def summary():
    printHeadline("Summary")
    print(f'tests passed {testsTaken - testsFailed}/{testsTaken}')
    if testsFailed == 0:
        print("Well Done!!")
    else:
        print('go into directory "failedTests" to see failure properties')

def parseArguments():
    parser = OptionParser()
    parser.add_option("-d", "--allowDelete", 
                    help="allow script to delete files.",
                    action="store_true")
    (options, args) = parser.parse_args()
    return vars(options)
                             
def main():
    try:               
        abspath = os.path.abspath(__file__)
        dname = os.path.dirname(abspath)
        os.chdir(dname)        
        if os.path.isdir(failedTestsDirName):
            if options['allowDelete']:
                shutil.rmtree(failedTestsDirName)
        createTmpWorkArea()            
        copyCompilationFiles()
        printHeadline("Generating lex.yy.c code using flex")    
        cmd = ['flex', '-o', os.path.join(tempDirName, 'lex.yy.c') , os.path.join(tempDirName, scannerFile)]
        runCommand(cmd)
        printHeadline("Compiling part 1")
        cmd = ['g++', '-std=c++11', os.path.join(tempDirName, 'lex.yy.c'), os.path.join(tempDirName, partAFile), '-o', os.path.join(tempDirName, 'tmptmptmp')]
        runCommand(cmd)
        printHeadline("Running tests")
        runTests()
        summary()
    except Exception as e:
        print("ERROR:")
        print(e)
        print("ABORTING")
        raise e
    finally:
        cleanExit()

if __name__ == "__main__":
    options = parseArguments()
    main()
            
