/*
 *	Implementation file for BigNumber class
 */
#include "BigNumber.h"
#include <iomanip>
//we'll need these everytime we call wouldOverflow
const long OVERFLOW_VALUE = LONG_MAX;
const std::string STR_OVERFLOW_VALUE = std::to_string(OVERFLOW_VALUE);
typedef std::vector<std::vector<unsigned char>*> numvec;
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

// check if the multiplication of two longs results in an overflow
bool BigNumber::doesOverflow(long& arg1, long& arg2) const{
		long tempProduct = arg1 * arg2;
		//if the signs of the arguments are the same and the sign of
		//the product is different, we know we overflowed. If not, just
		//initialize res and return it.
		if (((arg1 >= 0 && arg2 >= 0) && tempProduct <= 0) ||
			((arg1 <= 0 && arg2 <= 0) && tempProduct >= 0)){
			return true;
		}
		//if the signs are different and the total number of digits is 
		//less than 63, we always fit
		if (strlen(std::to_string(arg1).c_str()) + 
				strlen(std::to_string(arg2).c_str()) < 63){
			return false;
		}
		//if neither of the above cases is true, we probably overflow,
		//so do it the long way
		return true;
}


/*
 *	perform multiplication on two BigNumbers(the one calling the
 *	method and the one provided as the argument) and stores the output
 *	in the BigNumber output
 */
BigNumber BigNumber::multiply(BigNumber& input){
	//If neither number currently overflows long, and the product doesn't
	//overflow long, we can just use the normal multiplication operator
	//and return the object
	BigNumber res;
	//if either number is 0, just return a BigNumber with 0
	if (actualUnion.lnum == 0 || input.actualUnion.lnum == 0){
		return res = BigNumber(0);
	}
	if (!getOverflow() && !input.getOverflow()){
		if (!doesOverflow(actualUnion.lnum, input.actualUnion.lnum)){
		long product = actualUnion.lnum * input.actualUnion.lnum;
			return res = BigNumber(product);
		}

	}
	//in any other case, we do a lot more work
	char arg1[64];
	char arg2[64];
	char partialSum[64] = {0};
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
	//have to length check
	
	//perform the multiplication without simulation by walking 
	//through the array and doing memberwise multiplication with
	//carryover		
	std::vector<char*> partialSums;
	//use the longer one as the one to iterate through so the products
	//are the same
	if (myLength >= theirLength){
		for (int i = 0; i < myLength; ++i){
			symbMult(i, arg1, arg2, partialSum);
			char* c = new char[64]; 
			strcpy(c,partialSum);
			partialSums.push_back(c);
		}
	}
	else {
		for (int i = 0; i < theirLength; ++i){
			symbMult(i, arg2, arg1, partialSum);
			char* c = new char[64];
			strcpy(c, partialSum);
			partialSums.push_back(c);
		}
	}
	//to do the overflow checking, we just use the constructor, which
	memset(partialSum,0,64);	
	for (auto elem : partialSums){	
		std::string pSum = symbAdd(partialSum,elem);
		const char* sum = pSum.c_str();
		strcpy(partialSum,sum);
		delete[] elem;
	}	
	std::string finalSum(partialSum);
	//calls set and all that shit on the product
	res = BigNumber(finalSum);	
	return res;
}
//no relation to anything else, just here for the assignment
numvec* BigNumber::simulate_multiply(BigNumber& other){
	numvec* res = new numvec;
	std::vector<unsigned char>* mevec = vectorize();
	res->push_back(mevec);
	std::vector<unsigned char>* themvec = other.vectorize();
	res->push_back(themvec);
	//there are a number of intermediate steps equal to the number of
	//digits in me
	char intNum[64];
	char sumNum[64]={0};
	char maxSize=0; //we'll use this to get print's formatting nice
	for (int i = 0; i <mevec->size(); ++i){
		std::vector<unsigned char>* intVec = new std::vector<unsigned char>();
		memset(intNum,0,64);
		symbMult(i,(char*)number().c_str(),(char*)other.number().c_str(),intNum);
		strcpy(sumNum,(char*)symbAdd(sumNum,intNum).c_str());
		if (strlen(intNum) > maxSize){
			maxSize = strlen(intNum);
		}
		//push all the numbers into the intVec, then push that vec
		//into the return vector
		for (int j = 0; j < strlen(intNum); ++j){
			intVec->push_back(intNum[j]);
		}
		res->push_back(intVec);
	}
	//then the final result
	std::vector<unsigned char>* intVec = new std::vector<unsigned char>();
	std::string str(sumNum);
	stripLeadingZeros(str);
	strcpy(sumNum,str.c_str());
	for (int i=0; i < strlen(sumNum);++i){
		intVec->push_back(sumNum[i]);
	}
	res->push_back(intVec);
	//lastly, push a single char to the front of the vector with the max
	//size for pretty printing
	memset(intNum,0,64);
	intNum[0] = maxSize;
	intVec = new std::vector<unsigned char>();
	intVec->push_back(*intNum);
	res->insert(res->begin(),intVec);
	return res;
}

std::vector<unsigned char>* BigNumber::vectorize(){
	std::vector<unsigned char>* vec = new std::vector<unsigned char>();
	unsigned char num[64];
	strcpy((char*)num,number().c_str());
	for (int i = 0; i < strlen((char*)num); ++i){
		vec->push_back(num[i]);
	}
	return vec;
}

//has no relation to anything else, just here for the assignment
void BigNumber::print(BigNumber& other){
	//the very first element holds the max size of the elements, which
	//lets us do some pretty printing
	numvec* vec = simulate_multiply(other);
	std::vector<unsigned char>* phonyEle = (*vec)[0];
	int maxSize = phonyEle->front();
	delete phonyEle;
	//first arg
	phonyEle = (*vec)[1];
	std::string number;
	for (int i =0; i < phonyEle->size(); ++i){
		number+=(*phonyEle)[i];
	}
	std::cout<<std::setw(maxSize)<<number<<std::endl;
	delete phonyEle;
	//second arg
	phonyEle = (*vec)[2];
	std::cout<<"x";
	number="";
	for (int i =0; i < phonyEle->size();++i){
		number+= (*phonyEle)[i];
	}
	std::cout<<std::setw(maxSize-1)<<number<<std::endl;
	delete phonyEle;
	//problem line
	std::cout<<std::setw(maxSize+1)<<std::setfill('-')<<"\n";
	//all the intermediate numbers
	for (int i = 3; i < vec->size() - 1; i++){
		phonyEle = (*vec)[i];
		for (int j =0; j < phonyEle->size(); ++j){
			std::cout << (*phonyEle)[j];
		}
		delete phonyEle;
		std::cout << std::endl;
	}
	//final solution line
	std::cout << std::setw(maxSize + 1) <<std::setfill('-')<<"\n";	
	//and finally free the outer vec
	phonyEle = vec->back();
	number="";
	for (int i = 0; i < phonyEle->size(); i++){
		number+=(*phonyEle)[i];
	}
	delete phonyEle;
	std::cout<<std::setw(maxSize)<<std::setfill('0')<<number<<std::endl;
	 delete vec;
	

}
//performs symbolic multiplication on a single character that represents the step
//of the multiplication (how many 0's to put at the end) and two c-strings
//that represent numbers. Fills a result c-string with the product.
void BigNumber::symbMult(int pos, char arg1[64], char arg2[64], char res[64]){
	//clear res to be sure
	memset(res,0,64);
	//get my length
	int myLength = strlen(arg1);
	//get their length
	int theirLength = strlen(arg2);
	//set the length of the product, which can be at most one more than the
	//sum of the number of digits in the multiplication
	int prodLength = myLength + theirLength + 1;
	//get the appropriate character from me
	char c = arg1[myLength - 1 - pos];
	int val = c - '0';
	int carryover = 0;
	//fill in the fill 0s
	for (int i = pos; i > 0; --i){
		res[prodLength - 1] = '0';
		--prodLength;
	}
	//do a single iteration of multiplication
	//place the partial sum into the vector	
	for (int i = prodLength - 1; i >=0; --i){
		if (theirLength > 0){
			res[i] = val * (arg2[theirLength - 1] - '0') + carryover;				
			carryover = res[i] / 10;
			res[i] = res[i] % 10;
			res[i] = res[i] + '0';
			--theirLength;
		}
		//if we've hit the end of either of them, just fill in 0s
		else if (theirLength == 0){
			res[i] = '0' + carryover;
			carryover = 0;
		}
	}
	//fill in the top spot, which may just be 0
		res[0] = carryover + '0';

}
//performs symbolic additon on 2 c-strings and returns a similar char array
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
std::string BigNumber::number(){
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
