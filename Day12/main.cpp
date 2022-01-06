/*
 *	Program that creates a stub of a MyString class to demonstrate operator
 *	overloading
 */
#include <iostream>
#include <cassert>
#include <string.h>

using namespace std;

class MyString{
	private: 	
		//the cstring itself
		char* data;
		//the len of the string WITHOUT the null terminator
		int len;
		//helper that sets size and allocates for data
		int set_data(const char* string){
			int length = strlen(string);
			data = new char[length + 1];
			//strcpy null terminates for us
			strcpy(data, string);
			return length;
		}
		//helper to clean up memory for all the places that need this
		void cleanup(){
			if (data != nullptr){
				delete[] data;
				len = 0;
			}	
		}
		//default constructor
		MyString(){
			data = nullptr;
			len = 0;
		}
	public:
		
		//parameterized constructor
		MyString(const char* string){
			cout << "Parameterized constructor called" << endl;
			len = set_data(string);
			
		}
		
		//utility methods
		//get the data
		char* get_data(){
			return data;
		}
		//get length
		int length(){
			return len;
		}

		//reset the data
		void replace(const char* c){
			if (data != nullptr){
				delete[] data;
				len = 0;
			}
			len = set_data(c);
		}
		
		//copy constructor
		//remember this gets called when a value is being initialized
		//for the first time, so there is no case where data is not 
		//nullptr
		MyString(MyString& other){
			cout << "copy constructor called" << endl;
			len = set_data(other.data);
		}
		//move constructor
		MyString(MyString&& other){
			cout << "Move constructor called" << endl;
			//no case for this being initialized b/c constructor
			data = other.data;
			len = other.len;
			other.data = nullptr;
			other.len = 0;
	
		}
		
		//concatenation operator
		MyString operator+(MyString& other){
			int size = length() + other.length() + 1;
			MyString res;
			res.data = new char[size];
			//get all our stuff
			strcpy(res.data, data);
			//get their stuff
			strcpy(res.data + strlen(data), other.data);
			//null terminate
			res.len = size - 1;
			return res;

		}
		
		//multiplication operator
		MyString operator*(int num){
			int size = length() * num + 1;
			char temp[size];
			//populate the data string
			for (int i = 0; i < num; ++i){
				strcpy(temp + (i * length()),data);
			}
			//call the parameterized consturctor
			MyString res(temp);
			return res;	
		}

		//bracket/subscript operator, returns null if you try to pass
		//an out of bounds index
		char operator[](int pos){
			if (pos > len) return '\0';
			else return data[pos];
		}
		
		//copy assignment operator
		MyString& operator=(MyString& other){
			cout << "Copy assignment operator called" << endl;
			if (this == &other) return *this;
			cleanup();
			len = set_data(other.data);
			return *this;
		}
		//move assignment operator
		MyString& operator=(MyString&& other){
			cout << "Move assignment operator called" << endl;
			if (this == &other) return *this;
			cleanup();
			data = other.data;
			len = other.len;
			other.data = nullptr;
			other.len = 0;
			return *this;
		}
		//overload the cast to char* operator so we can do the string
		//literal comparisons (without this, the compiler warns about
		//"comparison with string literal is undefined"
		operator char*() const{
			return data;
		}
		//overload the equality check for literals
		 bool operator==(const char* s) const{
			return (!strcmp(data,s));
		}
		//destructor
		~MyString(){
			cout << "Destructor called" << endl;
			cleanup();
		}
		 
		//rvalue temporary operator (+)
		MyString operator+(long pos){	
			return std::move(MyString(data + pos));
		}
};

int main(){
	//basic functionality tests
	MyString s = "abc";
	assert(s == "abc");
	assert((s + s) == "abcabc");
	assert((s*3) ==  "abcabcabc");
	assert(s[2] == 'c');
	assert(s[5] == '\0');
	//doesn't work as intended yet
	assert((s + 1) == "bc");
	
	//tests for copy constructor and copy assignment operator
	MyString s2(s);
	assert(s2 == "abc");
	s2.replace("Hello");
	//check that s is still the same after s2 changes
	assert(s == "abc");
	s2 = s;
	assert(s2 == "abc");
	

	//test for move constructor and move assignment operator
	MyString s3 = std::move(MyString("lmao"));
	s2 = std::move(s);
	assert(s2 == "abc");
	//interestingly enough, if I use the cast operator rather than this
	//method, I get a segfault even though the cast operator just returns
	//the pointer. I wonder why exactly that happens?
	assert(s.get_data() == nullptr);

	return 0;
}
