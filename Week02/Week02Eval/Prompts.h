#ifndef PROMPTS_H
#define PROMPTS_H
void showLoginPrompt();
void showHomePrompt();
void quit();
void showAccountPrompt();
void showSearchPrompt();
void showNewAccountPrompt();
void searchCustomers();
void showAccounts(std::list<Customer>& customerList);
void displayAccount(std::list<Customer>& customerList);
void searchNames(std::list<Customer>& customerList);
void createAccount(std::list<Customer>& customerList, int& nextAccountNumber);
void closeAccount(std::list<Customer>& customerList);
bool checkSsn(std::string& ssn);
bool onlyLetters(std::string& word);
bool run_tests();
const std::string username = "demo";
const std::string password = "demo";	
#endif
