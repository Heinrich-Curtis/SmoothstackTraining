/*
 * This program parses an input string and, when the string corresponds to "int","double", or "char", the program
 * returns the size of that primitive type.
 *
 */ 
#include <iostream>

using namespace std;

int main(){
	
	cout << "Please enter 'int', 'double', or 'char'" << endl;
	std::string input;
	cin >> input;
	if (input == "int") cout << "The size of int is " << sizeof(int) << " bytes." << endl;
	else if (input == "double") cout << "The size of double is " << sizeof(double) << " bytes." << endl;
	else if (input == "char") cout << "The size of char is " << sizeof(char) << " bytes." << endl;
	else cout << "The only inputs accepted are 'int', 'double', or 'char'" <<  " bytes." << endl;
	return 0;	
}
