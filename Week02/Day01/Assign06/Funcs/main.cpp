/*
 *	Program that demonstrates how to invoke two overloaded methods who only
 *	differ in const-ness. The way to force the disambiguation of these 
 *	member functions is to make the object that calls the method const
 *	or non-const as well.
 */
#include <iostream>
#include <cassert>
using namespace std;

typedef struct Funcs {
		void myfunc(float f){
			cout << "myfunc() called" << endl;
		}
		void myfunc(float f) const{
			cout << "myfunc() const called" << endl;
		}
}Funcs;

int main(){
	//declare the structs and a float to pass to their member functions
	Funcs myStruct;
	const Funcs myConstStruct;
	float f = 3.0;

	//call the functions and check to make sure I called the right one
	myStruct.myfunc(f);
	myConstStruct.myfunc(f);
		

	return 0;
}
