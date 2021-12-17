/*
 *	Program that implements the algorithm for finding the best binary
 *	fraction representation of a floating point value
 */
#include <iostream>
#include <cassert>
#include <cmath>
#define DEBUG_FLAG

using namespace std;

/*
 *	find the best exponent by mult
 */

const unsigned long long J_min = (1LL << 52);
const unsigned long long J_max = (1LL << 53);

int find_best_n(double input){
	double result;
	//this could be made faster with binary search instead of linear,
	//but it's harder to structure and read that code
	for (int i = 0; i < 64; i++){
		result = input * (pow(2,i));
		if ((result >= J_min) && (result < J_max)){
			return i;
		}	
	}
	return 0;
}

int find_best_j(double value, int n){
	return 0;
}

int main(){
	double value;
	//we take in the float
	cin >> value;
	//we determine N (the exponent of 2)
	int n = find_best_n(value);
	#ifdef DEBUG_FLAG
		cout << "double is " << value << ", found exponent as " <<
		       n << endl;
	#endif	
	//assert(value == 0.1 && n == 56);
	
	//we find the best J (the numerator between 2^52 and 2^53)
	//we return the j, n and the float
	int j = find_best_j(value, n);
	//run some tests
	//cout << "size of long long: " << sizeof(long long) << endl;
	//cout << "J min: " << J_min << endl;
	//cout << "J max: " << J_max << endl;
	
	return 0;
}
