#!/bin/bash
flex scanner.lex
g++ -std=c++11 lex.yy.c part_a.cpp -o part_a.out
./part_a.out > ta1.res
diff ta1.res ta1.out
