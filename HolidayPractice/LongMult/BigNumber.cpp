/*
 *	Implementation file for BigNumber class
 */
#include "BigNumber.h"

//we'll need these everytime we call wouldOverflow
const long OVERFLOW_VALUE = LONG_MAX;
const std::string STR_OVERFLOW_VALUE = std::to_string(OVERFLOW_VALUE);
/*
 *	constructor sets the member to the provided value
 */
BigNumber::BigNumber(long num){
	//here is where we need to do the input validation, so any constructed
	//BigNumber is guaranteed to be a valid value
	set(num);
}

BigNumber::BigNumber(){
	set(0);
}

/*
 *	constructor that takes an std::string as an argument and tests if
 *	the argument would cause an integer overflow attempting to convert
 *	it to a numeric type. If so, then store it as a 64 char array instead.
 */
BigNumber::BigNumber(std::string& input){
	set(input);

}


/*
 *	perform multiplication on two BigNumbers(the one calling the
 *	method and the one provided as the argument) and stores the output
 *	in the BigNumber output
 */
BigNumber BigNumber::multiply(BigNumber& input, BigNumber& output){
	//get both numbers in their own arrays, a result object, and a
	BigNumber res;
	
	char arg1[64];
	char arg2[64];
	char partialSum[64];
	//get my number and convert to string if necessary
	if (getOverflow()){
		strcpy(arg1,actualUnion.cnum);
	}
	else {
		strcpy(arg1,std::to_string(actualUnion.lnum).c_str());
	}

	// get their number and convert to string if necessary
	if (input.getOverflow()){
		strcpy(arg2, input.actualUnion.cnum);
	}
	else {
		strcpy(arg2, std::to_string(input.actualUnion.lnum).c_str());
	}
	int myLength = strlen(arg1);
	int theirLength = strlen(arg2);
	//perform the multiplication without simulation by walking 
	//through the array and doing memberwise multiplication with
	//carryover		
	std::vector<long> partialSums;
	int carryOver = 0;
	int powerFor10 = 0;
	for ( int i = myLength - 1; i >= 0; --i){
		//refresh the partial sum every new digit
		memset(partialSum,0,64);
		for (int j = theirLength - 1; j >= 0; --j){
			; 
		}
	}
	//fill in with lead zeros if necessary
	//to do the overflow checking, we just use the constructor, which
	//calls set and all that shit on the product	
	return res;
}

//performs symbolic additon on 2 c-strings and returns an std::string
std::string BigNumber::symbAdd(const char arg1[64], const char arg2[64]){
	const char* larger;
	const char* smaller;
	int largerSize, smallerSize;
	if (strlen(arg1) >= strlen(arg2)){
		larger = arg1;
		smaller = arg2;
		largerSize = strlen(arg1);
		smallerSize = strlen(arg2);
	}	
	else {
		smaller = arg1;
		larger = arg2;
		smallerSize = strlen(arg1);
		largerSize = strlen(arg2);
	}
	char sum[largerSize + 2];
	int carryover = 0;
	sum[largerSize + 1] = '\0';
	while (largerSize > 0 || smallerSize > 0){
		if (smallerSize > 0){
			sum[largerSize] = (larger[largerSize-1] - '0') +
				(smaller[smallerSize-1] - '0')+ carryover;
		}
		else if (largerSize > 0){
			sum[largerSize] = larger[largerSize -1] - '0' + 
				carryover;	
		}
		//place the carryover in the final spot
		// move sum back down into the range it needs to be in to display chars
		carryover = sum[largerSize] / 10;
		sum[largerSize] = sum[largerSize] % 10;
		sum[largerSize] += '0';
		--largerSize;
		--smallerSize;
	}
	//place the carryover in the final spot
	sum[0] = carryover + '0';
	std::string res(sum);
	return res;
}
/*
 *	returns the data member of the class
 */
std::string BigNumber::number() const {
	if (!overflow){
	return std::to_string(actualUnion.lnum);
	}
	else {
		std::string result;
		for (int i = 0; actualUnion.cnum[i]!='\0'; i++){
			result += actualUnion.cnum[i];
		}
	return result;
	}

}

//get the overflow flag
bool BigNumber::getOverflow(){
	return overflow;
}

//get the lnum value from the union
long BigNumber::getLNum(){
	return actualUnion.lnum;
}

//get the cnum value from the union
char* BigNumber::getCNum(){
	return actualUnion.cnum;
}

/*
 *	set the value of the data member of the class, as well as the flags
 *	for overflow
 */
void BigNumber::set(long num){
	actualUnion.lnum = num;
	overflow = false;
	cNumStartIndex = 63;
}

/*
 *	The workhorse behind the logic for overflow and data member 
 *	representation. checks if the number represented by the string
 *	can fit in a 64-bit int. What should we do if the number is invalid?
 */
void BigNumber::set(std::string& input){
	//determine if the number is all numbers (it's a valid number)
	//if it isn't, put the object in an error state: overflow is on
	//but lnum is -1
	if (!isValidNumber(input)){
		overflow = true;
		actualUnion.lnum = -1;
		return;
	}
	//strip any leading 0s
	stripLeadingZeros(input);	
	//"pack down" the number (I'm gonna commit to this)
	//set overflow flag and cnumStartIndex
	if (wouldOverflow(input)){
		overflow = true;
		for (int i = 0; i < input.length(); ++i){
			actualUnion.cnum[i] = input[i];
		}
		//null terminate
		for( int i = input.length(); i < 64; ++i){
			actualUnion.cnum[i] = '\0';
		}	
		cNumStartIndex = 0;
	}
	else {
		overflow = false;
		actualUnion.lnum = std::stol(input);
	}

}

//checks if the provided input is all numeric digits (it's a number)

bool BigNumber::isValidNumber(std::string& input){
	//set up the regex
	std::regex number("-?[0-9]+");
	std::smatch res;
	//return if we get a match
	return std::regex_match(input, res, number);
}

//takes an input string and stips any leading 0's from it
void BigNumber::stripLeadingZeros(std::string& input){
	char res[input.length() + 1];
	strcpy(res,input.c_str());
	for (int i = 0; i < input.length(); i++){
		//set the start of the string as the first nonzero,
		//note that negative numbers will break this
		if (res[i] !='0'){
			input = &res[i];
			return;
		}
	}
}

//moves the actual numbers down to the end of the char array for easier math
//logic and sets the start Index field
int BigNumber::packDownNumString(std::string& input){
	//don't do anything for now, maybe use this later, gonna need to change
	//number() if we do
	return 0;
}

//checks if the numerical string passed as input would overflow a long
bool BigNumber::wouldOverflow(std::string& input){
	//we overflow if the number of digits in input is greater than
	//the number of digits in the string STR_OVERFLOW_VALUE
	//if we have exactly the same number of digits, then we have to do
	//a check to make sure every value starting at the top is AT MOST
	//the value in the limit string, note that we're fine as soon as we find
	//one digit in input that is less than the value in the overflow value	
	if (input.length() > STR_OVERFLOW_VALUE.length()){
	       	return true;
	}
	else if (input.length() < STR_OVERFLOW_VALUE.length()){
	       	return false;
	}
	
	else{
		for (int i = 0; i < STR_OVERFLOW_VALUE.length(); i++){
			if (input[i] < STR_OVERFLOW_VALUE[i]){
				return false;
			}
			else if (input[i] > STR_OVERFLOW_VALUE[i]){
				return true;
			}
		}
		//if we've made it this far, input is EXACTLY the limit so we're okay
		return false;
	}

	return false;
}
