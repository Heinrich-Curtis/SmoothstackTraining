/*
 *	Program that demonstrates the use of function pointers to perform
 *	operations on data
 */
#include <iostream>
#include <cassert>

using namespace std;
//functions we'll make pointers out of
int add(int a, int b) {return a + b;}
int subtract(int a, int b) {return a - b;}
int multiply(int a, int b) {return a * b;}

//global array of functions pointers
int (*func_ptrs[3])(int, int) = {add, subtract, multiply};

//compute function
int compute(int arg1, int arg2, unsigned char funcmask){
	//set up variables and logic controlling the function pointer
	int (*func)(int, int) = NULL;
	//note that because I'm using a bit check specifically, an input like
	//3 will actually cause this first if to fire. If I was using an 
	//equality check (funcmask == 1), this wouldn't happen. But the way I
	//read the assignment was to look at the set bits, so I did.
	if (funcmask & 0x1) func = func_ptrs[0];
	else if (funcmask & 0x2) func = func_ptrs[1];
	else if (funcmask & 0x4) func = func_ptrs[2];
	else {
		cout << "unrecognized func_mask. Mask was " << (int)funcmask << 
			endl;
		return 0;
	}
	//now we just call the function pointer and return the result
	return func(arg1,arg2);
}
int main(){
	
	//call compute with everything and make sure answers are correct
	unsigned char uc = 1;
	int arg1 = 3;
	int arg2 = 5;
	assert( compute( arg1, arg2, uc) == 8);
	uc = 2;
	assert( compute( arg1, arg2, uc) == -2);
	uc = 4;
	assert( compute( arg1, arg2, uc) == 15);
	//this case will pass the assert, but the "unrecognized func_mask"
	//message will be written to console
	uc = 8;
	assert( compute( arg1, arg2, uc) == 0);
	cout << "All tests passed." << endl;

	return 0;
}
