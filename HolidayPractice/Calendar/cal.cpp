/*
 *	Program that behaves similar to the unix cal command
 *
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <regex>

using namespace std;
//struct for months
typedef struct Month{
	string name;
	int numDays;	
}Month;

//months and days in them
Month months[13] = {
	{"Empty", 0},
	{"January", 31},
	{"February", 28},
	{"March", 31},
	{"April", 30},
	{"May", 31},
	{"June", 30},
	{"July", 31},
	{"August", 31},
	{"September", 30},
	{"October", 31},
	{"November", 30},
	{"December", 31}
};

//calendar header
const char daysHeader[21] = "Su Mo Tu We Th Fr Sa";

//enum for weekdays
typedef enum Week{
Sunday,
Monday,
Tuesday,
Wednesday,
Thursday,
Friday,
Saturday
} Week;

//calendar class
class Calendar{
	public:
		//Destructor
		~Calendar(){
			//just clean up the dynamically
			//allocated weeks in the calendar
			for (int i = 0; i < numWeeks; i++){
				delete[] calendar[i];
			}
		}
		//constructor
		Calendar(int month, int year){
			m_month = month;
			m_year = year;
			//use the time command to find the weekday for the 1st
			int startDay = getFirstDay();
			//check if it's a leap year
			if (month == 2 && isLeapYear(m_year)){
				months[2].numDays = 29;
			}
			//construct the array
			numWeeks = getNumWeeks(startDay);
			const int weeks = numWeeks;
			calendar = new int*[weeks];
			for (int i = 0; i < numWeeks; ++i){
				calendar[i] = new int[7];
			}
			//populate the entries with dates
			}
		
			//returns the calendar
			int** get() const{
				return calendar;
		}
		
			//prints the calendar
		void print() const{
			//print the month and year line
			printMonthAndYear();
			//print the days of the week
			printDaysHeader();
			//print the dates on the calendar
			for (int i = 0; i < numWeeks; ++i){
				for (int j = 0; j < 7; ++j){
					if (calendar[i][j] == 0){
						cout << "  ";
					}
					else{
						cout << calendar[i][j] << " ";
					}

				}
				cout << endl;
			}
		}
		
		//sets the month and year so we can build a calendar
		void set(int month, int year){
			
		}
	private:
		int m_month;
		int m_year;
		int numWeeks;
		int** calendar;
		//prints the line with the month and year
		void printMonthAndYear() const{

		}
		//prints the days header
		void printDaysHeader() const{
			cout<<daysHeader<<endl;
		}
		//calculates the weekday of the first day of the month
		int getFirstDay(){
		//put month and year into an appropriate string
		//query strptime for the day of the week
			return 1;
		}

		//has the rules for telling if it's a leap year
		bool isLeapYear(int year){
			if (year %4 == 0){
				if (year % 100 == 0){
					if (year % 400 == 0){
						return true;
					}
					return false;
				}
				return true;
			}
			return false;
		}
		//figure out how many rows out calendar is going to need
		int getNumWeeks(int startDay){
			//total number of days in the month plus the blanks
			//in the front
			numWeeks = (startDay + months[m_month].numDays)/7;
			//add one more for the blank week
			++numWeeks;
			return numWeeks;
		}

};

//prints the invocation rules
void usage(){
	cout<<"Incorrect invocation. Correct invocation is:"<<endl;
	cout<<"cal MM YYYY"<<endl;
	cout<<"where MM is a value between 1 and 12, and YYYY is a year"<<endl;
}

//make sure that the inputs are numbers that make sense
bool isValid(char* month, char* year){
	//use a regex to make sure both are numbers
	std::regex months("[0-9]?[0-9]");
	regex years("[0-9][0-9][0-9][0-9]");
	string smonth(month);
	string syear(year);
	cmatch res;
	if (regex_match( month, res, months)){
		return regex_match( year, res, years);
	}
	return false;
}



int main(int argc, char** argv){
	if (argc != 3){
		usage();
		return 1;
	}
	//check if month and year are valid
	if (!isValid(argv[1],argv[2])){
		usage();
		return 2;
	}
	//build a calendar object
	Calendar cal(argv[1], argv[2]);
	//print it
	cal.print();
	return 0;
}
