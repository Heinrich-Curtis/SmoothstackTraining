/*
 *	Program that puts ints and floats into an array of doubles (to ensure 
 *	all int values are representable), then uses a separate array that 
 *	holds the types of each element for determining that type late
 */
#include <iostream>
#include <cassert>

using namespace std;

int main(){
	
	int x = 1, y = 2, z = 3;
	float a = 1.2, b = 2.3, c = 3.0;
	double arr[] = { (double)x, (double)y, a, b, (double)z, c};
	//this array's job is to keep the type of each elements in arr. Messy
	//and a waste of space, but it fulfills the criteria of the assignment
	//A value of false means 'int', a value of true means float
	bool typeArr[] = {false, false, true, true, false, true};
	
	cout << "Determing types by separate data structure:" << endl;
	for (int i = 0; i < 6; i++){
		if (typeArr[i]){
			cout << arr[i] << " is a float value." << endl;
		}
		else {
			cout << arr[i] << " is an integer value."<< endl;
		}
	}
	return 0;
}
