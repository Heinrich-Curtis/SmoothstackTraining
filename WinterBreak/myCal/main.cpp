/*
 * Program that mimics that Linux builtin cal program - disalays the current
 * month in the terminal
 */

//struct for months
#include <iostream>
#include <string>


#define MONTHS_IN_YEAR 12
#define WEEKS_IN_MONTH 6
#define DAYS_IN_WEEK 7

typedef struct month{
	std::string monthName;
	std::string numOfDays;
} month;

//array that stores month names and their number of days
month months[12] = {
	{"January", "31"},
	{"February", "28"}

};

//print the month and year

//fill in the numbers

//figure out what day of the week the first day of the month is on

//highlight the number of the current day (have to get the current day)

int main(){
	for (auto i = 0; i < 2; i++){
		std::cout << months[i].monthName << std::endl;
	}	

	return 0;
}
