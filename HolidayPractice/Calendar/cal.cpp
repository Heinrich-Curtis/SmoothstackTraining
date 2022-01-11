/*
 *	Program that behaves similar to the unix cal command
 *
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <regex>
#include <math.h>
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
			delete[] calendar;
		}
		//constructor
		Calendar(int month, int year){
			set(month, year);
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
			//populate first week
			int nextDate=0;
			for (int i =0; i < 7; i++){
				if (i < startDay){
					calendar[0][i] = 0;
				}
				else {
					calendar[0][i] = ++nextDate;;
				}
			}
			//print all the middle weeks
			for (int i = 1; i < numWeeks;++i){
				for (int j = 0; j < 7; ++j){
					if (nextDate < months[m_month].numDays){
						calendar[i][j]=++nextDate;
					}
					else {
						calendar[i][j] = 0;
					}
				}
			}
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
						cout << "   ";
					}
					else{
						cout << setw(2)<<setfill('0')<<calendar[i][j] << " ";
					}
				}
				cout << endl;
			}
		}

		//sets the month and year so we can build a calendar
		void set(int month, int year){
			m_month = month;
			m_year = year;
		}
	private:
		int m_month;
		int m_year;
		int numWeeks;
		int** calendar;
		//prints the line with the month and year
		void printMonthAndYear() const{
			//find the number of blank spaces that should
			//print before the month name
			string name = months[m_month].name;
			//get the number of letters in the name
			int len = name.length();
			//fing the total number of spaces there will be around
			//the month and year
			int spaces = 21 - 5 - len;
			//take half of that for a mostly even look
			spaces = spaces /2;
			for (int i =0; i < spaces; ++i){
				cout<<" ";
			}
			//add the month name and the year and return
			cout<<name<< " "<<m_year<<endl;
		}
		//prints the days header
		void printDaysHeader() const{
			cout<<daysHeader<<endl;
		}
		//calculates the weekday of the first day of the month
		int getFirstDay(){
			//find the date of the first dat of the month given the month and year.
			//Uses Zeller's Algorithm
			int mon;
			int yea = m_year;
   			if(m_month > 2)
      			mon = m_month; //for march to december month code is same as month
   			else{
      			mon = (12 + m_month); //for Jan and Feb, month code will be 13 and 14
      			yea = m_year - 1; //decrease year for month Jan and Feb
   			}
   			int y = yea % 100; //last two digit
   			int c = yea / 100; //first two digit
   			int w = (1 + floor((13*(mon+1))/5) + y + floor(y/4) + floor(c/4) + (5*c));
   			w = w % 7;
   			//convert this saturday-based day to a sunday based day
			if (w == 0){
				w = 6;
			}	
			else{
				w--;
			}
			return w;
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
		if (regex_match( year, res, years)){
			int monthi = atoi(month);
			if (monthi > 0 && monthi < 13){
			return true;
			}
		}
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
	Calendar cal(atoi(argv[1]), atoi(argv[2]));
	//print it
	cal.print();
	return 0;
}
