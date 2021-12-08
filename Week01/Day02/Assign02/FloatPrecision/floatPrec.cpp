/*
 * Program that displays the property that the precision of a float decreases as the float becomes larger
 */ 
#include <iostream>
#include <iomanip>

using namespace std;
#define FLOAT_PRECISION 15

uint32_t set_exponent(uint32_t value, uint8_t newExp);
uint32_t set_mantissa(uint32_t value, uint32_t newMant);

int main(){
	//manually set some bits in a number, this value should be the IEEE 754 
	//encoding for the value "1.0"
	uint32_t num = 0x3f800000;
	//make a pointer so we can reinterperet these bits with pointer casts
	uint32_t* p_num = &num;
	
	/* print out some sequential floating point values so we can look
	 * at the difference between them. Any values between these are
	 * unrepresentable in ieee 754 and need to be corrected to one of
	 * them. This difference is a measure of precision. 
	*/
	cout << "Let's look at successive mantissa values for a given " <<
		"exponent." << endl;
	cout << "Exponent 0, mantissa 0: " << setprecision(FLOAT_PRECISION) <<
	       	*((float*)p_num) << endl;
	num = set_mantissa(num, 1);
	float mant_one =  *((float*)p_num); 
	cout << "Exponent 0, mantissa 1: " << setprecision(FLOAT_PRECISION) <<
	       	*((float*)p_num) << endl;
	num = set_mantissa(num, 2);
	float mant_two =  *((float*)p_num); 
	cout << "Exponent 0, mantissa 2: " << setprecision(FLOAT_PRECISION) <<
	       	*((float*)p_num) << endl;
	num = set_mantissa(num, 3);
	float mant_three =  *((float*)p_num); 
	cout << "Exponent 0, mantissa 3: " << setprecision(FLOAT_PRECISION) <<
	       	*((float*)p_num) << endl;
	
	/*
	 * Check to see if the difference between successive values is the same
	 */

	float first_exp_difference = mant_two - mant_one;	
	if ((mant_three - mant_two) == (mant_two - mant_one)){
		cout << "\nThe difference between successive mantissa values"<<
			" for an exponent is constant.\n" << endl;
	}
	else {
		cout << "\nThe difference between successive mantissa value "<<
			"is not the same for some reason.\n" << endl;
	}
	cout << "Now let's adjust the exponent part of the number.\n" << endl;
	
	//num is now the iee 754 representation for 2, which means the exponent
	//in the representation increased by 1. I have reset the mantissa bits
	//to 0.
	num = 0x40000000;
	cout << "Exponent 1, mantissa 0: " << setprecision(FLOAT_PRECISION) <<
	       	*((float*)p_num) << endl;

	num = set_mantissa(num, 1);
	mant_one = *((float*)p_num);
	cout << "Exponent 1, mantissa 1: " << setprecision(FLOAT_PRECISION) <<
	       	*((float*)p_num) << endl;
	num = set_mantissa(num, 2);
	mant_two = *((float*)p_num);
	cout << "Exponent 1, mantissa 2: " << setprecision(FLOAT_PRECISION) <<
	       	*((float*)p_num) << endl;
	num = set_mantissa(num, 3);
	mant_three = *((float*)p_num);
	cout << "Exponent 1, mantissa 3: " << setprecision(FLOAT_PRECISION) <<
	       	*((float*)p_num) << endl;


	//compare the differences for different exponents and draw a conclusion
	//from what we find	
	float second_exp_difference = mant_two - mant_one;	
	if ((mant_three - mant_two) == (mant_two - mant_one)){
		cout << "\nThe difference between successive mantissa values " <<
			"is still constant for a higher exponent." << endl;
	}
	else {
		cout << "\nThe difference between successive mantissa value " <<
			"for a bigger exponent changes." << endl;
	}
	if (second_exp_difference > first_exp_difference){
		cout << " \nBut the difference between successive values"<<
			" increases as the exponent increases, which means "<<
			"precision of floats goes down as the exponent " <<
			"part of the representation of the number goes up."<<
			endl;
	}
	else {
		cout << "\nThe difference between successive mantissa value" <<
			" does not increase as the exponent increases. This"<<
			" is not actually possible. Check your work."<< endl;
	}
	return 0;
}

/*
 *	set the exponent in the ieee 754 encoded number by 
 *	deleting the old one. Doesn't handle any special cases
 *	(overflow, etc.) 
 */

uint32_t set_exponent(uint32_t value, uint8_t newExp){
	value = value & 0x807FFFFF;
	uint32_t temp = newExp;
	value = value | (temp << 23);
 	return value;	
}

/*
 *	set the mantissa in the ieee 754 encoded number by deleting the old 
 *	mantissa bits and setting them from newMant. Doesn't handle
 *	any special cases (overflow, newMant > 23 bits, etc.) 
 */

uint32_t set_mantissa(uint32_t value, uint32_t newMant){
	value = value & 0xFF800000;
	return (value | newMant);
		
}

