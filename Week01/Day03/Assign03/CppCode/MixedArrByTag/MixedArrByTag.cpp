/*
 *	Program that stores dissimilar elements into an array by converting
 *	their data into pointers, then abusing the fact that my system is 
 *	64-bit so I have extra bits in the pointer to use as identifying 
 *	tags.
 */
#include <iostream>
#include <cassert>

uint32_t* convertIntToPtr(int i);
uint32_t* convertAndTagFloatToPtr(float f);
int convertPtrToInt(uint32_t* ptr);
float convertPtrToFloat(uint32_t* ptr);


using namespace std;

int main(){
	//if your system isn't 64-bit, this trick won't work
	assert(sizeof(uint32_t*) == 8);
	
	//make an array of pointers and a float and an int
	//note that float and int are at most 32 bits		
	uint32_t* arr[5];
	int x = 5;
	float y = 3.7;
	//convert to pointers using my helpers
	uint32_t* ptrFromInt = convertIntToPtr(x);
	uint32_t* ptrFromFloat = convertAndTagFloatToPtr(y);
	//put the pointers in the array
	arr[0] = ptrFromInt;
	arr[1] = ptrFromFloat;

	//remove the pointers from the array, convert them back to their 
	//original types and make sure that the values are the same
	int a;
	float b;
	long c = 0000000100000000;
	for (int i = 0; i < 2; i++){
		if (arr[i] & (uint32_t*)c){
			b = convertPtrToFloat(arr[i]);		
		}
		else {
			a = convertPtrToInt(arr[i]);
		}
	}

	assert (a == x);
	assert (b == y);

	return 0;
}

/*
 * converts an int to a pointer. By my own convention, ints are identified
 * by the lack of a "1" in bit 33
 */
uint32_t* convertIntToPtr(int i){
	return (uint32_t*)i;
}

/*
 * converts a float to a pointer. By my convention, floats are identified 
 * by a "1" in bit 33
 */
uint32_t* convertAndTagFloatToPtr(float f){
	uint32_t ptr = (uint32_t*)f;
	//if there are any bits in this number set to the left of position 32,
	//this method won't be reliable
	assert (ptr < (1 << 32));
	ptr = ptr | (1<<32);
	return ptr;
}

/*
 * converts a ptr back to an int
 */
int convertPtrToInt(uint32_t* ptr){
	return (int)ptr;	
}

/*
 * converts a ptr back to a float, getting the correct value back by 
 * removing the tag bit
 */
float convertPtrToFloat(uint32_t* ptr){
	//get rid of the tag bit by zeroing the 32 high bits
	ptr = ptr & 0x00000000FFFFFFFF;
	return (float)ptr;
}

