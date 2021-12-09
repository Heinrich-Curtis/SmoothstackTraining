/*
 * Program that stores ints and floats in an array of doubles (to make sure all
 * the values are representable). Once they're in there, the only options for
 * identifying which was which is to either A)Have a convention (for instance, 
 * "All ints go in odd-numbered slots and all floats go in even slots") or to 
 * have a separate data structure that holds each elements' type. 
 *
 */
#include <iostream>
#include <cassert>

using namespace std;

int main(){
	
	/*
	 * Here we use a convention: all integers are in even slots, and all
	 * floats are in odd slots
	 */
	int x = 1, y = 2;
	float f = 1.2, g = 2.0;
	double arr[4] = {(double)x, f, (double)y, g};
	
	cout << "Determing element type based on an established convention:" 
		<< endl;
	for (int i = 0; i < 4; i++){
		if (i % 2 == 0){
			cout << arr[i] << " this number is an int" << endl;
		}
		else {
			cout << arr[i] << " this number is a float" << endl;
		}
	}
	cout << endl;

	return 0;
}
