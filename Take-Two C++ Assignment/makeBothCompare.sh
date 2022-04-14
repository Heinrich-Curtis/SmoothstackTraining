#!/bin/bash
#make both versions of the program and check that their output is the same
INPUTFILE=wordlist.txt
#compile both with g++
g++ -o ver1 -g -Wall -Werror -std=c++17 main.cpp
g++ -o ver2 -g -Wall -Werror -std=c++17 main2.cpp
./ver1 $INPUTFILE
./ver2 $INPUTFILE
#check that their outputs are the same
diff result1.txt result2.txt
