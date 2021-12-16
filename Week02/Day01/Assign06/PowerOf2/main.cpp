/*
 *	Program that demonstrates how to determine if an input int is a
 *	power of 2. To do this, we just need to check that one and ONLY
 *	one bit is set in the number (because we're using the binary system,
 *	each new "binary place" represents the next power of 2: 2, 4, 8, etc.
 *	Note that no negative integers are powers of 2.
 */
#include <iostream>
#include <cassert>

/*
 *	walk through the bits of a number. Return true if and only if exactly 
 *	one bit (that is not the sign bit) is set. If the sign bit or more
 *	one of any of the other bits is set, x is not a power of 2.
 */
bool isPowerOfTwo(int x){
	//if the sign bit is set, this is a negative number and cannot
	//be a power of 2
	uint32_t mask = 0x80000000;
	if (mask & x) return false;
	//make a count of on bits.
	bool onlyFlipOnce = false;
	for (int i = 0; i < 32; i++){
		if (onlyFlipOnce){
			if (mask & x){
				return false;
			}
		}
		else{
			if (mask & x){
				onlyFlipOnce = !onlyFlipOnce;	
			}
		}
		mask = mask >> 1;
	}
	return onlyFlipOnce;
}



int main(){
	
	//I'm just going to throw some test cases right here in main since the 
	//function is defined above.
	assert(!isPowerOfTwo(-1));
	assert(!isPowerOfTwo(-2));
	assert(isPowerOfTwo(1));
	assert(isPowerOfTwo(2));
	assert(isPowerOfTwo(4));
	assert(!isPowerOfTwo(3));
	assert(isPowerOfTwo(1073741824));
	assert(!isPowerOfTwo(160));
	//0 is not a power of 2
	assert(!isPowerOfTwo(0));
}
