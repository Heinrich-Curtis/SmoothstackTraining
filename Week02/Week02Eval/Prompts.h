#ifndef PROMPTS_H
#define PROMPTS_H
#include "accounts.pb.h"
#include <string>
#include <list>

void showLoginPrompt();
void showHomePrompt();
void quit(week2Eval::AccountList& accountList, std::list<Customer>& customerList, const std::string& IOFileName, int nextAccountNumber);
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
int populateCustomerList(std::list<Customer>& customers, week2Eval::AccountList& accounts);
bool run_tests();
Transaction getTransactionData();
void printCustomerInfo(Customer& cus);
int parseInputToCurrency(std::string& input);
const std::string username = "demo";
const std::string password = "demo";	
#endif
