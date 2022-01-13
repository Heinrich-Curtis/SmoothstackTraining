/*
 *	headerfile that defines most of the functions related to the prompt,
 *	like recognizing args
 */
#ifndef PROMPTS_H
#define PROMPTS_H
#include <iostream>
#include <iomanip>
#include <vector>
#include <regex>

using namespace std;
//print the prompt to the screen
void printPrompt(){
	cout << "prompt>";	
}
//implicit convert to dec
//print output with required formatting (20 column wide number)
void prettyPrint(const string& output){
	//prompt is required on the answer lines as well
	cout << right <<setw(20) << output << endl;
}

void quit(){
	exit(0);
}

//check if the input is a decimal number
bool isDec(const string& input){
	string pattern = "[0-9]+";
	regex reg(pattern);
	smatch match;
	if (regex_match(input,match,reg)) return true;
	return false;
}
//check if the input is a hex number
bool isHex(const string& input){
	string pattern = "0x([0-9]|[a-f])+";
	regex reg(pattern);
	smatch match;
	if (regex_match(input,match,reg)) return true;
	return false;
	
}
//check if input is a binary number
bool isBin(const string& input){
string pattern = "0b[0-1]+";
	regex reg(pattern);
	smatch match;
	if (regex_match(input,match,reg)) return true;
	return false;
}

string addTwoNumbers(const string& s1, const string& s2){
//both arguments are converted to decimal and the response is in decimal
//according to the problem statement
	string arg1, arg2;
	if (isHex(s1)) { 
		arg1 = hexToDec(s1);
	}
	else if (isBin(s1)){
	       	arg1 = binToDec(s1);
	}
	else {
		arg1 = s1;
	}
	if (isHex(s2)) {
		arg2 = hexToDec(s2);
	}
	else if (isBin(s2)){
		arg2 = binToDec(s2); 
	}	
	else {
		arg2 = s2;
	}
	int num1 = stoi(arg1);
	int num2 = stoi(arg2);
	int numres = num1 + num2;
	string result = to_string(numres);

	return result;
}

//check that the input matches at least one of the three numeric types
bool isANumber(const string& input){
	if (isDec(input)) return true;
	if (isHex(input)) return true;
	if (isBin(input)) return true;
	return false;
}

//prints the erorr message
void printError(){
	string output = "Invalid number or command";
	prettyPrint(output);
}

//process input
void processInput(string& input){
	//tokenize the input
	vector<string> tokens;
	stringstream in(input);
	string term, output;
	while(getline(in,term, ' ')){
		tokens.push_back(term);
	}

	//, a quit command or an error
	if (tokens.front() == "quit") quit();
	if (tokens.front() == "hex"){
		//this is a conversion to hex request
		if (isANumber(tokens[1])){
			if (isHex(tokens[1])){
				prettyPrint(tokens[1]);	
			}
			else if (isDec(tokens[1])){
				output = decToHex(tokens[1]);
				prettyPrint(output);	
			}
			else if (isBin(tokens[1])){
				output = binToHex(tokens[1]);
				prettyPrint(output);
			}
		}
		else{
			printError();
		}
	}
	else if (tokens.front() == "bin"){
		if (isANumber(tokens[1])){
			if (isBin(tokens[1])){
				prettyPrint(tokens[1]);
			}
			else if (isDec(tokens[1])){
				output = decToBin(tokens[1]);
				prettyPrint(output);
			}
			else if (isHex(tokens[1])){
				output = hexToBin(tokens[1]);
				prettyPrint(output);
			}
		}
		else{
		       	printError();
		}
			
	}
	else if (isANumber(tokens.front())){
	//if the leading string isn't bin or hex, it's either a request to
	//convert to decimal, or it's an addition
		if (tokens.size() == 1){
		//asking to convert decimal to decimal, or invalid
			if (isANumber(tokens[0])){
				if (isDec(tokens[0])){
					prettyPrint(tokens[0]);
				}
				else if (isHex(tokens[0])){
					output = hexToDec(tokens[0]);
					prettyPrint(output);
				}
				else if (isBin(tokens[0])){
					output = binToDec(tokens[0]);
					prettyPrint(output);
				}	
			}
			else{
				printError();
			}
		}
		else if (tokens.size() == 3){
		//the addition case
			if (isANumber(tokens[0]) && (tokens[1] == "+") && 
				(isANumber(tokens[2]))){
				output = addTwoNumbers(tokens[0],tokens[2]);
				prettyPrint(output);						
			}
			else{
				printError();
			}
		}
		else{
			printError();
		}

	}
	else {
		printError();
	}
	//look at each arg to see if we're an operator or a number
	//or an invalid value (you're either one of the valid operators
	//or a number


}
#endif
