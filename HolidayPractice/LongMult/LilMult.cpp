/*
 *	driver for BigNumber program, this is the version that doesn't use any
 *	classes or do any overflow protection,, the very first part of the 
 *	assignment
 */
#include "BigNumber.h"
#include <iostream>
#include <cassert>
#include <regex>
#include <vector>
#include <cmath>
#include <iomanip>

//can only comma separate these in gnu++17 lmao
using std::cout;
using std::cin;
using std::endl;
void noClassLongMult();
//#define MANUALSWITCH

int main(int argc, char** argv){
#ifdef MANUALSWITCH
	noClassLongMult();
#endif
#ifndef MANUALSWITCH
	BigNumber onetwofour(124);
	BigNumber fourfivesix(456);
	onetwofour.print(fourfivesix);
	return 0;
#endif
}

//function that runs the classless version of this program: asks for two
//operands and performs the long multiplication
void noClassLongMult(){
	//the first step is to just write code that performs multiplication on
	//values received from stdin, doing it the long way
	std::string firstArg, secondArg;	
	cout << "Let's do long multiplication" << endl;
	cout << "Give me the first argument:" << endl;
	cin >> firstArg;
	//validate first arg
	//pattern for regexes (one or more numeric digits)
	std::regex number("[0-9]+");
	//here's where a list of matches is stored
	//you need a SMATCCH to match a string variable, and a CMATCH to match
	//against an immediate 
	std::smatch regexRes;
	//only get past this if we have a valid number input
	while (!std::regex_match(firstArg, regexRes,number)){
		cout << "please enter a valid number only" << endl;
		cin >> firstArg;
	}


	cout << "Give me the second argument:" << endl;
	cin >> secondArg;
	//validate second arg
	while (!std::regex_match(secondArg, regexRes,number)){
		cout << "please enter a valid number only" << endl;
		cin >> secondArg;
	}
	
	cout << "Performing long multiplication:" << endl;
	//all we need to do is to save all the partial sums along the way so we
	//can display them at the end
	//just set the width to be 12 for now and we can adjust later (the 
	//product will be at most as many as the sum of digits of the inputs)
	cout << " " << std::setw(12) << std::right << firstArg << endl;
	cout << "x" << std::setw(12) << std::right << secondArg << endl;
	cout << "---------" << endl;
	std::vector<long> partialSums;
	long firstArgNum = atol(firstArg.c_str());
	//each partial sum is just the result of multiplying one digit of one 
	//argument by the entire second argument, so get each digit and perform
	//the multiplication, then save the result in partialSums
	//the arguments are still strings, so we can iterate through them by
	//position and know all the sizes and stuff
	//long secondArgNum = atol(secondArg.c_str());
	//cout << "secondArgNum: " << secondArgNum << endl;		
	for (auto i = 0; i < secondArg.length() ; ++i){
		//get the next digit from the arg
		char c = secondArg.at(secondArg.length() - i - 1);
		//turn it into a number
		long cn = atol(&c);
		partialSums.push_back(cn * firstArgNum * pow(10,i));

	}	
	//now partialSums has all the partial sums, so we can print out
	//the entire solution
	long sum = 0;
	for (const auto &it : partialSums){
		cout << std::setw(13) << std::right << it << endl;
		//increment the final sum
		sum += it;
	}
	//print the final solution
	cout << "---------" << endl;
	cout << std::setw(13) << std::right << sum << endl;
}

