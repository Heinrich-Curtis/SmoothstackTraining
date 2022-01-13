/*
 *	Program that does some simple number conversion and calculations to demonstrate
 *	use of streams
 */
#include <iostream>
#include <iomanip>
#include <string>
#include "Numbers.h"
#include "Prompts.h"
#include <cassert>
using namespace std;

int main(){
	
	string input;
	string output;
	//tests for number conversions
	string s1 = "123";
	string s2 = "0x7b";
	string s4 = "0xb07";
	string s3 = "0b1111011";
	assert(decToBin(s1) == s3);
	assert(decToHex(s1) == s2);
	assert(binToHex(s3) == s2);
	assert(binToDec(s3) == s1);
	assert(hexToBin(s2) == s3);
	assert(hexToDec(s2) == s1);
	//test for pattern matching
	assert(isDec(s1));
	assert(!isDec(s2));
	assert(!isDec(s3));
	assert(isHex(s2));
	assert(isHex(s4));
	assert(!isHex(s1));
	assert(!isHex(s3));
	string s = "ab0g";
	assert(!isHex(s));
	assert(isBin(s3));
	assert(!isBin(s1));
	assert(!isBin(s2));
	assert(!isBin(s));
	assert(isANumber(s1));
	assert(isANumber(s2));
	assert(isANumber(s3));
	assert(!isANumber(s));
	string done = "1";
	string dtwo = "2";
	string dthree = "3";
	string hone = "0x1";
	string htwo = "0x2";
	string bone = "0b1";
	string btwo = "0b10";
	assert(addTwoNumbers(done, dtwo) == dthree);
	assert(addTwoNumbers(hone, htwo) == dthree);
	assert(addTwoNumbers(bone, btwo) == dthree);
	
	while(true){
		printPrompt();
		getline(cin, input);	
		processInput(input);	
	}
	
	return 0;
}
