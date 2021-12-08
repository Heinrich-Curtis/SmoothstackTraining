/*
 * Program that displays the property that the precision of a float decreases as the float becomes larger
 */ 
#include <iostream>
#include <iomanip>

using namespace std;

uint32_t increment_exponent(uint32_t value);

int main(){
	//manually set some bits in a number, this value should be the IEEE 754 
	//encoding for the value "1.0"
	uint32_t num = 0x3f800000;
	//make a pointer so we can reinterperet these bits with pointer casts
	uint32_t* p_num = &num;
	cout << "float 1: " << setprecision(12) << *((float*)p_num) << endl;
	num++;
	cout << "float 1: " << *((float*)p_num) << endl;
	num++;
	cout << "float 1: " << *((float*)p_num) << endl;
	num = 0x40000000;
	cout << hex << num << endl;
	cout << "float 1: " << *((float*)p_num) << endl;
	num++;
	cout << "float 1: " << *((float*)p_num) << endl;
	num++;
	cout << "float 1: " << *((float*)p_num) << endl;

	uint32_t j = 128;
	uint32_t val = j << 23;
	cout << "j << 23 = " << val << endl;
	val =increment_exponent(val);
	cout << "j++ << 23 = " << hex << val << endl;
	return 0;
}

/*
 *	increment the exponent in the ieee 754 encoded number. Doesn't handle
 *	any special cases (overflow, etc.) 
 */

uint32_t increment_exponent(uint32_t value){
	uint32_t temp = value >> 23;
	temp++;
	value = temp << 23;
 	return value;	
}

/*
 *	increment the mantissa in the ieee 754 encoded number. Doesn't handle
 *	any special cases (overflow, etc) 
 */

uint32_t increment_mantissa(uint32_t value){
	
}

