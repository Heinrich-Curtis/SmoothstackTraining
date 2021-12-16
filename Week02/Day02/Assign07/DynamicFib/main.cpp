/*
 *	This program uses dynamic programming to compute the fibonacci
 *	sequence and populate an array, saving intermediate results and
 *	using them for the next computation rather than solving the same
 *	subproblems more than once. We use the data in the array to determine
 *	exactly when integer overflow occurs in the sequence. Using dynamic 
 *	programming for this problem was suggested/allowed on the discord server.
 */
#include <iostream>
#include <cassert>

#define ARRAY_SIZE 50

using namespace std;
void populateFibArray(int arr[ARRAY_SIZE]){
	arr[0] = 0;
	arr[1] = 1;
	arr[2] = 1;
	//saving the intermediate results means we don't need to recalculate
	//them multiple times, providing huge speedup and saving stack memory
	for (int i = 3; i < ARRAY_SIZE; i++){
		arr[i] = arr[i - 1] + arr[i - 2];
	}
}

int main(){

	//get the array started. I'm gonna start putting terms in slot 1 rather
	//than 0, just so it's easy to see which term we're looking at by array
	//index
	int FibTerms[50];
	populateFibArray(FibTerms);

	//do some testing here to ensure our values are correct
	assert(FibTerms[0] == 0);
	assert(FibTerms[1] == 1);
	assert(FibTerms[2] == 1);
	assert(FibTerms[3] == 2);
	assert(FibTerms[4] == 3);
	assert(FibTerms[5] == 5);
	assert(FibTerms[46] == 1836311903);

	//now that we have the terms, we can walk through the array and see 
	//where we overflowed int by checking when the fibonacci values 
	//suddenly decrease.The value before overflow occurs is the largest
	//fibonacci value that fits into the type
	for (int i = 1; i < ARRAY_SIZE; i++){
		if (FibTerms[i] < FibTerms[i-1]){
		cout << "Evidence of overflow at term " << i <<". Last valid"<<
			" value is " << FibTerms[i-1] << " at position " << 
			i-1 << "." << endl;
			break;
		}
	}
}
