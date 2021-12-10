/*
 *	A program that just contains the random pieces of code that test the 
 *	conditions in today's writeup.
 */
#include <iostream>
#include <cassert>
using namespace std;
//just put each question's material in it's own function for clarity
void questionOne();
void questionTwo();
void questionFour();

int main(){
	
	questionOne();
	questionTwo();	
	questionFour();
	return 0;
}

void questionOne(){
//#include #include this gives an error "expected "FILENAME" or <FILENAME>",
//but I thought this was just a copy-paste typo in the assignment question
//anyway
assert(3 == 3.0);
float x = 3.1; 
//assert(x == 3.1); 
assert(3.1 == 3.1); 
assert(true == 1.0); 
assert('a' == 97); 
int* p = 0; 
assert(NULL == p); 
assert(NULL == 0); 

}

void questionTwo(){
	cout << "Question Two: " << endl;
	cout << "Type id of an int is " << typeid(int).name() << endl;
	cout << "Type id of an float is " << typeid(float).name() << endl;
	cout << "Type id of an char is " << typeid(char).name() << endl;
	cout << "Type id of an bool is " << typeid(bool).name() << endl;
	cout << "Type id of a double is " << typeid(double).name() << endl;	
	int i = 1;
	float f = 2.0;
	char c = 'a';
	bool b = true;
	cout << "-----------------------------------------------" << endl;
	cout << " The artithmetic result of an int and int is " << 
		typeid(i + i).name() << endl;
	cout << " The artithmetic result of an float and float is " << 
		typeid(f + f).name() << endl;
	cout << " The artithmetic result of an bool and bool is " << 
		typeid(b + b).name() << endl;
	cout << " The artithmetic result of an char and char is " << 
		typeid(c + c).name() << endl;

	cout << "-----------------------------------------------" << endl;
	cout << " The artithmetic result of an int and float is " << 
		typeid(i + f).name() << endl;
	cout << " The artithmetic result of int and char is " << 
		typeid(i + c).name() << endl;
	cout << " The artithmetic result of int and bool is " << 
		typeid(i + b).name() << endl;
	cout << " The artithmetic result of float and char is " << 
		typeid(f + c).name() << endl;
	cout << " The artithmetic result of float and bool is " << 
		typeid(f + b).name() << endl;
	cout << " The artithmetic result of char and bool is " << 
		typeid(c + b).name() << endl;
	
}

void questionFour(){
	int x = 4;
	int y = x+++2;

	assert(y == 6);
	assert(x == 5);
}

