/*
 *	Program that implements the algorithm for finding the best binary
 *	fraction representation of a floating point value
 */
#include <iostream>
#include <cassert>
#include <cmath>
#include <iomanip>
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
	//but t's harder to structure and read that code
	for (int i = 0; i < 64; i++){
		result = input * (pow(2,i));
		if ((result >= J_min) && (result < J_max)){
			return i;
		}	
	}
	return 0;
}
//just do this with a linear search for now. Change it to a binary search later?
long long find_best_j(double value, int n){
	return ceil(value * (pow(2,n)));
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
	long long j = find_best_j(value, n);
	
	//print the output
	cout << "J = " << j << ", N = " << n << endl;
	cout << setprecision(15) << j/pow(2,n) << endl;
	//run some tests
	assert (find_best_n(0.125) == 55);
	//cout << "J max: " << J_max << endl;
	assert (find_best_j(0.125, 55) == 4503599627370496);	
	return 0;
}
