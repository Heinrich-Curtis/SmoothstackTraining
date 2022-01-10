/*
 *	Header file for BigNumber class
 */
#ifndef BIGNUMBER_H
#define BIGNUMBER_H
#include <regex>
#include <string>
#include <vector>
#include <iostream>
#include <limits.h> //MAX_LONG value

class BigNumber{
	private:
		bool overflow;
		union {
			long lnum;
			char cnum[64];
		} actualUnion;
		int cNumStartIndex;
		//helper methods
		bool wouldOverflow(std::string& input);
		void stripLeadingZeros(std::string& input);
		int packDownNumString(std::string& input);
		bool doesOverflow(long& arg1, long& arg2) const;
		
	public:
		BigNumber();
		BigNumber(long num);
		BigNumber(std::string& input);
		BigNumber multiply(BigNumber& input);
		void symbMult(int pos, char arg1[64], char arg2[64], 
				char res[64]);
		std::string number();
		void set(long num);
		void set(std::string& input);
		bool getOverflow();
		//diagnostic methods
		long getLNum();
		char* getCNum();
		//helper methods
		bool isValidNumber(std::string& input);
		std::string symbAdd(const char arg1[64], const char arg2[64]);
		//weird things for the assignment
		typedef std::vector<std::vector<unsigned char>*> numvec;
		numvec* simulate_multiply(BigNumber& other);
		void print(BigNumber& other);
		std::vector<unsigned char>* vectorize();


		
		
				
};


#endif
