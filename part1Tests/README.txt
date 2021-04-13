to run tests:
1) Copy the files to the server.
2) Make sure you have the files 'part_a.cpp', 'tokens.hpp', 'scanner.lex' in the SAME directory of the script
3) Maybe you need to use the command 'chmod a+x' on the script to have access to it
4) Just do "./activateTests.py" and thats it! if you want the script to clean after hemself, and to clean the
    failed tests directory when activated, run the script with -d flag. like so 
    "./activateTests.py -d" use at your own risk

WHAT HAPPENS IF TEST FAILS?
    if tests will fail, it will create a directory named "failedTests". 
    inside that folder, you will find directory for each test that failed, and inside that directory there will be
    NAME.in, NAME.out, NAME.testout , which are the input file, the expected output file, and the output of the test.


HOW TO ADD TESTS?
    to add tests, just add 2 files in the tests directory, in and out. for example, if i created a new test named 'testi'
    i will create 2 files 'testi.in', 'testi.out' and put them in the tests directory.
    'testi.in' is the input and 'testi.out' is the expected output

ENJOY!
