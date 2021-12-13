/*
 * A class that encapsulates a customer's data
 */ 
#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <string>
#include <time.h>

class Customer{
	private:
	std::string m_firstName;
	std::string m_lastName;
	std::string m_ssn;
	std::string m_dateOpened;
	std::string m_accountNumber;
	public:
	//overloaded constructor. There is no default, all fields are 
	//required
	Customer(std::string firstName, std::string lastName, std::string
			ssn, std::string accNum){
		m_firstName = firstName;
		m_lastName = lastName;
		m_ssn = ssn;
		m_dateOpened = setDateOpened();
		m_accountNumber = accNum;
	}
	
	//getters and setters
	std::string getFirstName(){
		return m_firstName;
	}

	void setFirstName(std::string firstName){
		m_firstName = firstName;
	}
	
	std::string getLastName(){
		return m_lastName;
	}

	void setLastName(std::string lastName){
		m_lastName = lastName;
	}

	std::string getSsn(){
		return m_ssn;
	}

	void setSsn(std::string ssn){
		m_ssn = ssn;
	}

	std::string getDateOpened(){
		return m_dateOpened;
	}

	std::string setDateOpened(){
		std::string dateString, monString, yearString;
		time_t rawTime;
		struct tm* timeinfo;
		time(&rawTime);
		timeinfo = localtime(&rawTime);
		dateString = asctime(timeinfo);
		monString = dateString.substr(4,6);
		yearString = dateString.substr(19,5);
		dateString = monString + yearString;
		return dateString;
	}
	
	void setAccNum(int accNum){
		m_accountNumber = accNum; 
	}
	
	std::string getAccountNumber(){
		return m_accountNumber;
	}
	//required overload to be able to remove from customerList
	bool operator == (const Customer& cus) const {
		return m_ssn == cus.m_ssn;
	}

	bool operator != (const Customer& cus) const {
		return !operator==(cus);
	}

};



#endif
