/*
 *	Header file for numberical operations
 */
#ifndef NUMBERS_H
#define NUMBERS_H
#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
using namespace std;
//input has already been validated to be a decimal number at this point
string decToBin(string input){
	//get number
	int strnum = std::stoi(input);
	if (strnum == 0) return "0";
	string result;
	//populate result
	while(strnum > 0){
		if (strnum % 2 == 1){
			result = "1" + result;
		}	
		else {
			result = "0" + result;
		}
		strnum = strnum / 2;
	}
	result = "0b" + result;
	return result;
}
//takes a decimal number and converts it to a hex number
string decToHex(string input){
	int strnum = std::stoi(input);
	if (strnum == 0){
	return "0x0";
	}
	string result;
	while (strnum > 0){
		switch (strnum % 16){
		case 0 :
			result = "0" + result;
			break;
		case 1:
			result = "1" + result;
			break;
		case 2: 
			result = "2" + result;
			break;
		case 3:
			result = "3" + result;
			break;
		case 4:
			result = "4" + result;
			break;
		case 5:
			result = "5" + result;
			break;
		case 6:
			result = "6" + result;
			break;
		case 7:
			result = "7" + result;
			break;
		case 8:
			result = "8" + result;
			break;
		case 9:
			result = "9" + result;
			break;
		case 10:
			result = "a" + result;
			break;
		case 11:
			result = "b" + result;
			break;
		case 12:
			result = "c" + result;
			break;
		case 13:
			result = "d" + result;
			break;
		case 14:
			result = "e" + result;
			break;
		case 15:
			result = "f" + result;
			break;
		}
		strnum = strnum / 16;
	}
	
	result = "0x" + result;
	return result;
}

//convert string to decimal
string binToDec(string input){
	string result;
	if (input == "0b0"){
		result = "0";
		return result;
	}
	int numres = 0;
	for (int i = input.size() - 1; i > 1; --i){
		int exp = input.size() - i - 1;
		if (input[i] == '1'){
			numres += pow(2,exp);
		}
	}
	result = to_string(numres);
	return result;
}

//convert a binary string to hex
string binToHex(string input){
	string result;
	if (input == "0b0"){
		result = "0x0";
		return result;
	}
	result = binToDec(input);
	result = decToHex(result);
	return result;
}
//hex to decimal
string hexToDec(string input){
	string result;
	if (input == "0x0"){
		result = "0";
		return result;
	}
	int numres = 0;
	int base = 0;
	for (int i = input.size() - 1; i > 1; --i){
		int exp = input.size() - i - 1;
		if (input[i] == 'a'){
			base = 10;
		}
		else if (input[i] == 'b'){
			base = 11; 
		}
		else if (input[i] == 'c'){
			base = 12;
		}
		else if (input[i] == 'd'){
			base = 13;
		}
		else if (input[i] == 'e'){
			base = 14;
		}

		else if (input[i] == 'f'){
			base = 15;
		}
		//if we're not one of the 5 letters, we're a number
		else {
			base = input[i] - '0';
		}
		numres += (base * pow(16,exp));	
	}
	//make numres back into a string and return it;
	result = to_string(numres);
	return result;
}

string hexToBin(string input){
	string result;
	if (input == "0x0"){
		result = "0b0";
		return result;
	}
	result = hexToDec(input);
	result = decToBin(result);
	return result;
}
#endif
