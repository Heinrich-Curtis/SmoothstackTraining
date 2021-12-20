/*
 * Week 1 eval assignment. Creates a dummy bank cli that asks user for a login 
 * and supports some simple commands.
 *
 */
#include <iostream>
#include "Customer.h"
#include <string>
#include <stdlib.h>
#include <list>
#include <iomanip>
#include <cassert>
#include "Prompts.h"
#include "Transaction.h"
//Protobuf related stuff
#include "accounts.pb.h"
#include <fstream>

using namespace std;
//#define DEBUG

//static test function declarations
static bool runTransactionTests();
static bool parseCurrencyTests();
static bool getTransDataTests();
static bool runCustomerTests();

int main(){
	GOOGLE_PROTOBUF_VERIFY_VERSION;
	#ifdef DEBUG
		bool result = run_tests();
		if (result) cout << "All Tests Passed"<<endl;
	#else
		showLoginPrompt();
	#endif
		
	return 0;
}

//handles initialy user authentication. Terminates the program after 3 failed
//login attempts
void showLoginPrompt(){
	std::string entered_user, entered_pw;
	for (int numAttempts = 0; numAttempts < 3; numAttempts++){
	cout << "username: ";	
	cin >> entered_user;
	cout << endl <<"password: ";
	cin >> entered_pw;
	cin.ignore();
	if (entered_user == username && entered_pw == password){
		cout << "Authenticated"<<endl;
		showHomePrompt();
		}
	else {
		cout << "Username or password incorrect" << endl;
		}	
	}
	//if we make it here, the login attempt has failed 3 times, so we quit
	exit(0);
}

//displays the home prompt and handles all the commands that can be executed
void showHomePrompt(){
	week2Eval::AccountList accountList;
	std::list<Customer*>* customerList = new std::list<Customer*>();
	const std::string iOFileName = "accountsIO.pb";
	int nextAccountNumber = 1;
	//since we've logged in, we read from the input file and populate
	//the customer list if necessary here
	
	fstream input(iOFileName, ios::in | ios::binary);
	//if we can't read it, make it
	if (!input){
		cout << iOFileName<<" not found. Creating new file." << endl;
	}
	//if there's something wrong, say something
	else if (!accountList.ParseFromIstream(&input)){
		cerr << "Failed to parse address book." << endl;
		return;
	}
	
	//
	nextAccountNumber = populateCustomerList(customerList, accountList);
	//clear the account list to prevent the double saving?
	accountList.Clear();
	
	//close the input file so it can be used later
	input.close();
	std::string homeCommand;
	//Customer cus("James","John", "111111111","1");
	//cus.setAccNum(to_string(++nextAccountNumber));
	//customerList.push_front(cus);
	while(true){
		cout << endl;
		cout << "Enter a command:" 	<< endl;
		cout << "\t1- show accounts" 	<< endl;
		cout << "\t2- display account"	<< endl;
		cout << "\t3- search name" 	<< endl;
		cout << "\t4- new account"	<< endl;
		cout << "\t5- close account"	<< endl;
		cout << "\t6- quit"		<< endl;
		cout << "home>";	
		getline(cin,homeCommand);
		if (homeCommand == "quit" || homeCommand == "6") {
			quit(accountList, customerList, iOFileName,
					nextAccountNumber);
		}
		else if (homeCommand == "show accounts" || homeCommand == "1"){
			showAccounts(customerList);
		}
		else if (homeCommand == "display account" || homeCommand == "2"){
			displayAccount(customerList);
		}
		else if (homeCommand == "search name" || homeCommand == "3"){
			searchNames(customerList);
		}
		else if (homeCommand == "new account" || homeCommand == "4"){
			createAccount(customerList, nextAccountNumber);
		}
		else if (homeCommand == "close account" || homeCommand == "5"){
			closeAccount(customerList);
		}
		else {
			cout << "Please enter a valid command." << endl;
		}
	}
}

//handles the "quit" command by exiting the program
void quit( week2Eval::AccountList& accountList,
	std::list<Customer*>* customerList , const std::string& IOFileName,
	int nextAccountNumber){
	//logic for writing to the file and then closing that resource go here
	for (Customer* cus : *customerList){
	week2Eval::Account* account  = accountList.add_accounts();
		account->set_first_name(cus->getFirstName());
		account->set_last_name(cus->getLastName());
		account->set_account_number(cus->getAccountNumber());
		account->set_ssn(cus->getSsn());
		account->set_date_opened(cus->getDateOpened());
		account->set_balance(cus->getBalance());
		//customerList->remove(cus);
		//delete cus;
		//have to serialize transactions here too
	}
	delete customerList;
	/*
	 *now we've written all the changes, so save it to the file and quit
	 *We want truncate flag here because the database should reflect
	 *all the changes made during the program running, which can 
	 *include removing accounts. So we just save the customer list
	 *into the database
	 */
	if (accountList.accounts_size() > 0){
		accountList.set_next_available_account(nextAccountNumber);
		fstream outFile(IOFileName, ios::out | ios::trunc | ios::binary);

	if (!outFile){
		cout << "Failed to open the output file.Creating?" << endl;
	}
	if (!accountList.SerializeToOstream(&outFile)){
		cout << "Failed to write the account list." << endl;
	}
	outFile.close();
	}
	
	google::protobuf::ShutdownProtobufLibrary();
		
	cout << "logged out" << endl;
	exit(0);
}

//handles the behavior of the show account command
void showAccounts(std::list<Customer*>* customerList){
	if (customerList->empty()){
		cout <<"There are no accounts" << endl;
	}
	else{
		for (Customer* customer : *customerList){
		int dollars = customer->getBalance() / 100;
		int cents = customer->getBalance() % 100;
		cout << setfill(' ') << setw(10) << std::left << 
		customer->getFirstName() << " ";
		cout << setw(10) << customer->getLastName() << " ";
	        cout << "$" <<setw(6) << std::right<< dollars; 
		cout << std::right << "." << setw(2) << setfill('0') << cents << " ";
	        cout << setfill('0') << "#" << std::right << setw(5) << 
			customer->getAccountNumber();
	        cout << " " << customer->getDateOpened() << endl;
		}	
	}
}

//handles the behavior of the display account command
void displayAccount(std::list<Customer*>* customerList){
//show the new prompt
	std::string accNum;
	cout << "account>";
	cin >> accNum;
	cin.ignore();
	bool found = false;
	Customer* outerCus;
	for (Customer* cus : *customerList){
		if (cus->getAccountNumber() == accNum){
			found = true;
			outerCus = cus;
			printCustomerInfo(cus);
			break;
		}
	}
	//if we got here, it means we didn't find a matching account
	if (!found){
		cout << "invalid account" << endl;
		return;
	}
	//here we let you add transactions
	//cin.ignore(); // flush the buffer
	cout << "1: add transaction" << endl;
	cout << "2+: Return Home" << endl;
	string input;
	getline(cin, input);
	if (input =="add transaction" || input == "1"){
		//add the transaction
		Transaction tr = getTransactionData();
		/*
		cout << "Transaction has type" << tr.printType() <<
			" and amount " << tr.getAmount() << endl;
			*/
		//now we have the data so we add it to the account
		if (!outerCus->isTransactionPossible(tr)){
			cout << "Insufficient balance." << endl;
			}	
		//the credit case
		else {
			outerCus->adjustBalance(tr);
			outerCus->registerTransaction(tr);
		}

	}
	//2 or something else
	else{
		return;
	}
	cin.ignore();

}

//searches the customer list. Any partial matches are pushed on the back
//total matches are pushed to the front. Then 
void searchNames(std::list<Customer*>* customerList){
 //start a new list
	std::list<Customer*> searchResults;
	cout << "name>";
 //use an iterator to go through customers and check first and last name
 	std::string fullName,firstName, lastName;
	getline(cin, fullName);
	firstName = fullName.substr(0,fullName.find(" "));
	//watch for the case here where only one name has been added
	lastName = fullName.substr(firstName.length()+1,fullName.length() - 
			firstName.length());
	//cout << firstName << " " << lastName << endl;
	//cout << "customer list size: " << customerList.size();	
 	for (Customer* cus : *customerList){
		//the exact match case
		//cout << cus.getFirstName() << cus.getLastName();
		if (cus->getFirstName() == firstName && cus->getLastName() == 
			lastName){
			searchResults.push_front(cus);
		}
		//the one or the other case
		else if (cus->getFirstName() == firstName || cus->getLastName() 
				== lastName){
			searchResults.push_back(cus);
		}

	}
	if (searchResults.empty()) {
		cout << "No matching accounts" <<endl;
		//cin.ignore();
		return;
	}
	//now we print out the search results
	int resultNumber = 1;
	for ( Customer* cus : searchResults){
		cout << resultNumber++ << ". " << cus->getFirstName() << " " <<
			cus->getLastName() << endl;
	}
	//home option at the end
	cout << "Home Select Number > "<< resultNumber - 1 << endl;
	cout << "number>";
	int resultSelection = resultNumber;
	cin >> resultSelection;
	//int response = atoi(resultSelection);
	//cout << resultSelection;
	
	if (resultSelection >= resultNumber){
		cin.ignore();
		return;
	}
	else{
		//print the customer data
		std::list<Customer*>::iterator it = searchResults.begin();
		for (int i = 1;i < resultSelection; i++){
			//cout << *it;
			++it;
		}
		//Customer* cus = searchResults[resultSelection - 1];
		Customer* cus = *it;
		std::string fullSsn = cus->getSsn();
		std::string hiddenSsn = fullSsn.substr(5,4);
		cout << cus->getFirstName() << " " << cus->getLastName() <<
			" " << hiddenSsn << " " << cus->getDateOpened() << " " <<
			 setfill('0') << setw(8) << cus->getAccountNumber() << 
			 endl;
	       cin.ignore();	
	}

}

//create a new account, prompting for each piece separately
void createAccount(std::list<Customer*>* customerList, int& nextAccountNumber){
	std::string fullName, firstName, lastName, ssn;
	bool isValid = false;
	while(true){
		
		cout << "Customer first name>";	
		cin >> firstName;
		isValid = onlyLetters(firstName);
		if (!isValid){
			cout << "Names should only use letters" << endl;
			cin.ignore();
			continue;
		}
		cout << "Customer last name>";
		cin >> lastName;
		isValid = onlyLetters(lastName);
		if (!isValid){
			cout << "Names should only use letters" << endl;
			cin.ignore();
			continue;
		}
		break;
		/*
		 * getline(cin, fullName);
		//cin.ignore();
		firstName = fullName.substr(0,fullName.find(" "));
		cout << "___"<<firstName<<"___"<<endl;
		//watch for the case here where only one name has been added
		lastName = fullName.substr(firstName.length()+1,fullName.length() - 
			firstName.length());
		cout <<"___"<<lastName<<"___"<<endl;
		isValid = onlyLetters(firstName);
		if (!isValid){
			cout <<"Names should only use letters and" << 
				" spaces." << endl;
			continue;
			
			}
		isValid = onlyLetters(lastName);
		if (!isValid){
			cout <<"Names should only use letters and" <<
				" spaces." << endl;
			continue;
			}
		*/
			
		}
	while(true){
		//now we have a valid name, we can ask for an ssn
		cout << "SSN>";
		cin >> ssn;
		isValid = checkSsn(ssn);
		for (Customer* cus : *customerList){
			if (cus->getSsn() == ssn){
				cout<< "This person already has an account"
					<< endl;
				cin.ignore();
				return;
			}
		}
		if (!isValid){
			cout << "SSNs should be exactly 9 numerals long"<<endl;
			continue;
			}
		cin.ignore();
		break;

	}
	//if we made it here, that means the name and ssn are valid, so we make
	//a new account and push it onto the customer list
	Customer* newCus= new Customer(firstName,lastName, ssn, to_string(nextAccountNumber++)); 
	customerList->push_back(newCus);


}

//search the customer list by account number to locate the account, then
//ask for confirm to delete before deleting
void closeAccount(std::list<Customer*>* customerList){
	cout << "account>";
 //use an iterator to go through customers and check first and last name
 	std::string accountNum;
	cin >> accountNum;
	/* handle leading 0s here
	for (int i = 0; i < accountNum.length(); i++){
		if (accountNum[i] ==
				}
	*/

	//cout << firstName << " " << lastName << endl;
	//cout << "customer list size: " << customerList.size();	
 	for (Customer* cus : *customerList){
		if (cus->getAccountNumber() == accountNum){
			cout << "Are you sure you want to delete account number "<<
				cus->getAccountNumber()<< "? (y/n)"<<endl;
			char input;
			cin >> input;
			if (input == 'y' || input == 'Y'){
				customerList->remove(cus);
				delete cus;
				cin.ignore();
				return;
				}
			}

		}
	//we couldn't find that account number
	cout << "No such account."<< endl;
	cin.ignore();

}

bool onlyLetters(std::string& word){
	//if we're outside the english ascii characters or in that little
	//space between Z and A, we're wrong.
	for (int i = 0; i < word.length(); i++){
		if (word[i] < 'A' || word[i] > 'z') return false;
		if (word[i] > 'Z' && word[i] < 'a') return false;
	}
	return true;
}


//checks that an SSN is all numbers and 9 digits long
bool checkSsn(std::string& ssn){
	if (ssn.length() != 9) return false;
	for (int i = 0; i < 9; i++){
		if (ssn[i] < '0' || ssn[i] > '9') return false;
	}
	return true;
}

//populate the customer list from what we retrieve from the accounts list file
int populateCustomerList(std::list<Customer*>* customers, week2Eval::AccountList& accounts){
		
	for (int i = 0; i < accounts.accounts_size();i++){
		Customer* cus = new Customer();
		const week2Eval::Account& account = accounts.accounts(i);
		cus->setFirstName(account.first_name());
		cus->setLastName(account.last_name());
		cus->setSsn(account.ssn());
		cus->setAccountNumber(account.account_number());
		cus->setDateOpened(account.date_opened());
		cus->setBalance(account.balance());
		customers->push_back(cus);
	}
	return accounts.next_available_account();
}
//get the required info to build a transaction. Returns the amount -1 if 
//you did something invalid, triggering the loop in display
Transaction getTransactionData(){
	string type;
	while (type != "credit" && type != "debit"){
		cout << "Enter credit or debit" << endl;
		getline(cin, type);
	}
	Transaction::TrType trType;
	if (type == "credit") {
		trType = Transaction::TrType::CREDIT;
	}
	else {
		trType = Transaction::TrType::DEBIT;
	}
	
	cout << "Enter an amount in dollars and cents." << endl;
	string input;
	cin >> input;
	//try to parse the string 
	int money=parseInputToCurrency(input);
	if ( money == -1){
		cout << "Please enter a positive number in decimal notation" << endl;
		Transaction tr(Transaction::TrType::DEBIT,-1);
		return tr;
	}
	else{
		// just build the transaction and return it
		Transaction tr(trType, money);
		return tr;
	}
	
}
//take an input string and turn it into an amount of cents if it's valid
int parseInputToCurrency(string& input){
	//neg number means invlaid
	int amount=-1;
	string dollarsPart = input.substr(0,input.find('.'));
	string centsPart = input.substr(input.find('.')+1,input.length());
	const char* dollarsP = dollarsPart.c_str();
	const char* centsP = centsPart.c_str();
	int dollars = atoi(dollarsP);
	int cents = atoi(centsP);
	if (dollars < 0 || cents < 0){
		return -1;
	}
	else {
		amount = dollars * 100 + cents;
	}
	return amount;
	//parse the string for the decimal point
	
}
//prints a customer's information to the terminal, used by display
void printCustomerInfo(Customer* cus){
	std::string fullSsn = cus->getSsn();
	std::string hiddenSsn = fullSsn.substr(5,4);
	cout << cus->getFirstName() << " " << cus->getLastName() <<
		" " << hiddenSsn << " " << cus->getDateOpened() << " " <<
		setfill('0') << setw(8) << cus->getAccountNumber() << 
		endl;
	
}

//runs a bunch of tests
bool run_tests(){
	//test customer
	Customer cus("John","James","111111111","10");
	assert(cus.getAccountNumber() == "10");
	assert(cus.getFirstName() == "John");
	assert(cus.getLastName() != "John");
	
	//show functionality of overloaded equals/not equals
	Customer cus2("Talib","James","111111112","12");
	assert(cus != cus2);
	Customer cus3("Jeff","James","111111111","12");
	assert(cus == cus3);

	//test prompts and helpers
	std::list<Customer> customerList;
	assert(customerList.empty());
	customerList.push_back(cus);
	assert(customerList.size() == 1);
	customerList.push_back(cus2);
        assert(customerList.size() == 2);
	std::string badSsn = "11111111";
	
	//fails because ssn too short
	assert(!checkSsn(badSsn));
	badSsn = "11111111a";
	
	//fails because letter
	assert(!checkSsn(badSsn));
	badSsn = "1111111111";
	
	//fails because too long
	assert(!checkSsn(badSsn));
	badSsn = "111111111";
	
	//passes
	assert(checkSsn(badSsn));	
	std::string badName = "Ja4mes";

	//fails because number
	assert(!onlyLetters(badName));
	
	badName = "Jame$s";
	//fails because symbol
	assert(!onlyLetters(badName));

	badName = "James";
	//passes
	assert(onlyLetters(badName));
	cout << "Prompt tests passed" << endl;
	//this takes customer list as an argument because of how closeAccount is written
	//to automate these tests, redirect input from "testingInput.txt"
	cout << "Close an account in an empty list here" << endl;
	std::list<Customer*>* cusList = new std::list<Customer*>();
	closeAccount(cusList);
	//use account 12 here
	assert(cusList->size() == 0);
	
	//add account 12 here with 111111114
	cout << "Add account 12 with ssn 111111114" << endl;
	int nextAccount = 1;
	createAccount(cusList, nextAccount);
	assert(cusList->size() == 1);
	delete cusList;
	cout << "Prompt tests passed" << endl;
	//call other testing functions	
	runCustomerTests();
	runTransactionTests();
	parseCurrencyTests();
	getTransDataTests();
	//etc

	return true;	
}

//additional unit tests for Customer class, most have already been tested
//in the prompt tests
static bool runCustomerTests(){
	Customer cus1;
	assert(cus1.getBalance() == 0);
	assert(cus1.getDateOpened() == "");
	std::string newDate = "Dec 5 1950";
	cus1.setDateOpened(newDate);
	assert(cus1.getDateOpened() != cus1.setDateOpened()); 
	cout << "Customer unit tests passed" << endl;
	return true;
}
//unit tests for transaction class
static bool runTransactionTests(){
	//transaction tests
	Transaction tr(Transaction::TrType::DEBIT, 100);
	tr.setType(Transaction::TrType::DEBIT);
	tr.setAmount(100);
	assert(tr.getEffectiveDate() == "Dec 20 2021");
	assert(tr.getType() != Transaction::TrType::CREDIT);
	assert(tr.getAmount() == 100);
	tr.setType(Transaction::TrType::CREDIT);
	assert(tr.getType() == Transaction::TrType::CREDIT);	
	cout << "Transaction unit tests passed" << endl;
	//more tests here for customers with transactions, adding transactions
	Customer cus("James","Joyce","111111111","1");
	//not enough money
	tr.setType(Transaction::TrType::DEBIT);
	assert(!cus.isTransactionPossible(tr));
	tr.setType(Transaction::TrType::CREDIT);
	assert(cus.isTransactionPossible(tr));
	cus.adjustBalance(tr);
	assert(cus.getBalance() == 100);
	assert(cus.getTransactions()->empty());
	cus.registerTransaction(tr);
	assert(!cus.getTransactions()->empty());
	assert(cus.getTransactions()->front().getAmount() == tr.getAmount());
	cout << "Customer and Transaction integration tests passed" << endl;
	return true;
}
//tests for parseInputToCurreny function
static bool parseCurrencyTests(){
	std::string input ="-1.10 ";
	assert (parseInputToCurrency(input) == -1);
	input = "119.37";
	assert(parseInputToCurrency(input) == 11937);
	return true;
}

//tests for getTransactionData function, input data is passed from
//testingInput.txt
static bool getTransDataTests(){
	//credit with a negative amount
	Transaction tr = getTransactionData();
	assert(tr.getAmount() == -1);
	//type is debit because that's what shows up for invalid value
	assert(tr.getType() == Transaction::TrType::DEBIT);
	//credit with a positive amount
	tr = getTransactionData();
	assert(tr.getAmount() == 1137);
	assert(tr.getType() == Transaction::TrType::CREDIT);
	//debit with a negative amount
	tr = getTransactionData();
	assert(tr.getAmount() == -1);
	assert(tr.getType() == Transaction::TrType::DEBIT);
	//debit with a positive amount
	tr = getTransactionData();
	assert(tr.getAmount() == 1423);
	assert(tr.getType() == Transaction::TrType::DEBIT);
	return true;
}

