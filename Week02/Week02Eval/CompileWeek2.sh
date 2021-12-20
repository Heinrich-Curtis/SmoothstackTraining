#!/bin/bash

#just a command to run the compilation command with the linked libraries. Turn
#this into a make file
echo "clang++ -o bankcli -Wall -g -std=c++17 -L/usr/local/lib\
	-lprotobuf Week2Eval.cpp accounts.pb.cc"

	clang++ -o bankcli -Wall -g -std=c++17 -L/usr/local/lib \
	-lprotobuf Week2Eval.cpp accounts.pb.cc
