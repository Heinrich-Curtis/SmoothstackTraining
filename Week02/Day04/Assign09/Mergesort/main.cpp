/*
 *Program that demonstates the use of a member function pointer to act as a
 comparator
 */
#include <iostream>
#include <cassert>
#include <string>
#include <vector>

using namespace std;

struct Student{
	string studentID;
	int score;
	bool comparator(Student x, Student y);

};


//used by sort, uses the comparator from student to 
void mergeSort(vector<Student>& studentList, bool (*comp)(Student x, Student y)){
	//do recursion here
	


class MergeSort{
	public:
		void sort(vector<Student>& students, Student s){
			bool (*comp)(Student x, Student y) = (Student::comparator);
			return mergeSort(students, comp);
		}


};

}
int main(){
	//initialize students and a list, populate the list
	Student std1 = {"0001", 80};
	Student std2 = {"0002", 90};
	Student std3 = {"0003", 75};
	vector<Student> studentList;
	studentList.push_front(std1);
	studentList.push_front(std2);
	studentList.push_front(std3);
	//sort the list using the comparator
	
	//make sure the list is sorted

}
