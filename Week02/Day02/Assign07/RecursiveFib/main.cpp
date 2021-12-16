/*
 *	Program that recursively computes the first 50 terms of the fibonacci
 *	sequence. There is an issue because the fibonacci terms overflow
 *	a 32-bit number before we hit 50. To detect the overflow, we can just
 *	check every newly-computed number and see if it's smaller than the 
 *	previous term (that means we've overflowed the integral type). We 
 *	could also listen for the overflow signal, but that's much more 
 *	complicated. The program doesn't crash except if I leave the 
 *	bottom-most assert live in the code (the assert fails as a result 
 *	of the overflow), but I DO get a warning from clang that the 
 *	bottom-most assert will always be false (it is part of a warning 
 *	I've never seen before, '-Wtautological-constant-out-of-range-compare',
 *	which is kind of neat.
 *
 *	But no, the program doesn't notify me in any way that an arithmetic
 *	overflow occured at runtime.
 *
 */
#include <iostream>
#include <cassert>

#define ARRAY_SIZE 50
using namespace std;
/*
 *	Finds the nth term of the fibonacci series by recursion
 */
int Fib(int num){
	if (num < 1) return 0;
	if (num == 1 || num == 2) return 1;
	else {
		return Fib(num - 1) + Fib(num - 2);
	}
}

int main (){
	//check a couple known fibonacci values to ensure correctness of the
	//function
	assert(Fib(-10) == 0);
	assert(Fib(0) == 0);
	assert(Fib(1) == 1);
	assert(Fib(2) == 1);
	assert(Fib(3) == 2);
	assert(Fib(4) == 3);
	assert(Fib(5) == 5);
	//skip a couple
	assert(Fib(46) == 1836311903);
        //now we have a problem
	//assert(Fib(47) == 2971215073);
	//populate an array as requested in the assignment
	int arr[ARRAY_SIZE];	
	for (int i = 0; i < ARRAY_SIZE; i++){
		arr[i] = Fib(i);
	}
	return 0;
}
