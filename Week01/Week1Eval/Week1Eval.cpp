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

using namespace std;
//#define DEBUG



int main(){

	#ifdef DEBUG
		bool result = run_tests();
		if (result) cout << "Tests Passed"<<endl;
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
	std::list<Customer> customerList;
	int nextAccountNumber = 1;
	std::string homeCommand = "";
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
		if (homeCommand == "quit" || homeCommand == "6") quit();
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
void quit(){
	cout << "logged out" << endl;
	exit(0);
}

//handles the behavior of the show account command
void showAccounts(std::list<Customer>& customerList){
	if (customerList.empty()){
		cout <<"There are no accounts" << endl;
	}
	else{
		for (Customer customer : customerList){
			cout << customer.getFirstName() << " " << 
				customer.getLastName() << " " <<
				setfill('0') << setw(8) <<
			       customer.getAccountNumber() << " " <<	
				customer.getDateOpened() << endl;
		}	
	}
}

//handles the behavior of the display account command
void displayAccount(std::list<Customer>& customerList){
//show the new prompt
	std::string accNum;
	cout << "account>";
	cin >> accNum;
	cin.ignore();
	//bool found = false;
	for (Customer cus : customerList){
		if (cus.getAccountNumber() == accNum){
	//	found = true;
		std::string fullSsn = cus.getSsn();
		std::string hiddenSsn = fullSsn.substr(5,4);
		cout << cus.getFirstName() << " " << cus.getLastName() <<
			" " << hiddenSsn << " " << cus.getDateOpened() << " " <<
			 setfill('0') << setw(8) << cus.getAccountNumber() << 
			 endl;
		return;
		}
	}
	//if we got here, it means we didn't find a matching account
	cout << "invalid account" << endl;
}

//searches the customer list. Any partial matches are pushed on the back
//total matches are pushed to the front. Then 
void searchNames(std::list<Customer>& customerList){
 //start a new list
	std::list<Customer> searchResults;
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
 	for (Customer cus : customerList){
		//the exact match case
		//cout << cus.getFirstName() << cus.getLastName();
		if (cus.getFirstName() == firstName && cus.getLastName() == 
			lastName){
			searchResults.push_front(cus);
		}
		//the one or the other case
		else if (cus.getFirstName() == firstName || cus.getLastName() 
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
	for ( Customer cus : searchResults){
		cout << resultNumber++ << ". " << cus.getFirstName() << " " <<
			cus.getLastName() << endl;
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
		std::list<Customer>::iterator it = searchResults.begin();
		for (int i = 1;i < resultSelection; i++){
			//cout << *it;
			++it;
		}
		//Customer* cus = searchResults[resultSelection - 1];
		Customer cus = *it;
		std::string fullSsn = cus.getSsn();
		std::string hiddenSsn = fullSsn.substr(5,4);
		cout << cus.getFirstName() << " " << cus.getLastName() <<
			" " << hiddenSsn << " " << cus.getDateOpened() << " " <<
			 setfill('0') << setw(8) << cus.getAccountNumber() << 
			 endl;
	       cin.ignore();	
	}

}

//create a new account, prompting for each piece separately
void createAccount(std::list<Customer>& customerList, int& nextAccountNumber){
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
		for (Customer cus : customerList){
			if (cus.getSsn() == ssn){
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
	Customer newCus(firstName,lastName, ssn, to_string(nextAccountNumber++));
	customerList.push_back(newCus);


}

//search the customer list by account number to locate the account, then
//ask for confirm to delete before deleting
void closeAccount(std::list<Customer>& customerList){
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
 	for (Customer cus : customerList){
		if (cus.getAccountNumber() == accountNum){
			cout << "Are you sure you want to delete account number "<<
				cus.getAccountNumber()<< "? (y/n)"<<endl;
			char input;
			cin >> input;
			if (input == 'y' || input == 'Y'){
				customerList.remove(cus);
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

bool run_tests(){
	bool result = true;
	//test customer
	Customer cus("John","James","111111111","10");
	assert(cus.getAccountNumber() == "10");
	assert(cus.getFirstName() == "John");
	assert(cus.getLastName() != "John");
	assert(cus.getDateOpened() == "Dec 13 2021");
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

	closeAccount(customerList);
	//use account 12 here
	assert(customerList.size() == 1);
	
	//add account 12 here with 111111114
	int nextAccount = 4;
	createAccount(customerList, nextAccount);
	assert(customerList.size() == 2);



	return result;
}
