/*
 * A class that encapsulates a customer's data: account information and 
 * transaction history
 */ 
#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <string>
#include <time.h>
#include <vector>
#include "Transaction.h"
#include <iostream>
class Customer{
	private:
	std::string m_firstName;
	std::string m_lastName;
	std::string m_ssn;
	std::string m_dateOpened;
	std::string m_accountNumber;
	int m_balance;
	std::vector<Transaction>* m_transactionHistory;

	public:
	Customer(){
		m_firstName = "";
		m_lastName = "";
		m_ssn = "";
		m_dateOpened = "";
		m_balance = 0;
		m_transactionHistory = new std::vector<Transaction>();
	}
	Customer(std::string firstName, std::string lastName, std::string
			ssn, std::string accNum){
		m_firstName = firstName;
		m_lastName = lastName;
		m_ssn = ssn;
		m_dateOpened = setDateOpened();
		m_accountNumber = accNum;
		m_balance = 0;
		m_transactionHistory = new std::vector<Transaction>();
	}
	
	//I know I need this custom destructor because I dynamically allocate
	//for the transaction history on construction
	//TODO: Change program structure (or maybe customer/transaction
	//relationship) to avoid issues leaking memory and creating dangling
	//pointers inside containers (think about how search copies things
	//and when destructors get called
	~Customer(){
		//std::cout << "inside of Customer's destructor" <<std::endl;
		//delete m_transactionHistory;
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

	void setDateOpened(const std::string& otherDate){
		m_dateOpened = otherDate;
	}
	
	void setAccountNumber(std::string accNum){
		
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

	void setBalance(int balance){
		m_balance = balance;
	}

	int getBalance(){
		return m_balance;
	}
	
	//get a pointer to the transaction history
	std::vector<Transaction>* getTransactions(){
		return m_transactionHistory;
	}
	//there is no setter for transaction history. I don't think it makes any
	//sense to be able to delete a transaction history, but I can see in the
	//future there may be a want to delete transactions from a transaction
	//history
	
	//checks to make sure that a transaction is possible
	bool isTransactionPossible(Transaction& tr){
		if (tr.getType() == Transaction::TrType:: DEBIT){
			if (tr.getAmount() > m_balance){
			       return false;	
			}
		}
		return true;	
	}

	//applies a transaction to the account balance, returns the new
	//balance (security issue?)
	int adjustBalance(Transaction& tr){
		if (tr.getType() == Transaction::TrType::DEBIT){
			m_balance -= tr.getAmount();
		}
		else {
			m_balance += tr.getAmount();
		}
		return m_balance;
	}
	
	//registers a transaction with the account by adding it to the 
	//transaction history of the account
	bool registerTransaction(Transaction& tr){
		try{
			m_transactionHistory->push_back(tr);
		}
		//if something goes wrong, return false	
		catch(std::exception e){
			return false;
		}
		return true;
	}

};



#endif
