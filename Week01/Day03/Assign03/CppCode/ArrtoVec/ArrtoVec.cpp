//Program that copies elements of an array to a vector then prints them

#include <iostream>
#include <vector>
#include <cassert>
#include <iomanip>

using namespace std;

int main(){
	//declare/initialize our containers
	vector<float> myVec;
	float arr[] = { 1.0, 2.0, -3.75};
	
	//copy the array elements into the vector
	for (int i = 0; i < 3; i++){
		myVec.push_back(arr[i]);
	}
	
	//check and make sure the contents are identical in the containers
	for (int i = 0; i < 3; i++){
		assert(arr[i] == myVec[i]);
	}
	
	//print the elements as requested, in a single line with an EOL at the end
	for (int i = 0; i < 3; i++){
		cout << myVec[i] << " ";
		if (i == 2) cout << endl;
	}
/*	I read the assignment differently at first, I don't need this
	cout << "----------------------------------------" << endl;

	for (int i = 0; i < 3; i++){
		cout << arr[i] << endl;
	}
*/
	return 0;
}

