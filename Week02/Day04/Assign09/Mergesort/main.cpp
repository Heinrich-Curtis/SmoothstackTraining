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
	static bool comparator(Student x, Student y){
		return x.score < y.score;
	}

};





class MergeSort{
	private: 
		//used by sort, uses the comparator from student to 
		void mergeSort(vector<Student>& studentList, int begin, int end){
			//if the size of the list is 1, just return that list
			if (begin == end) return;
			//if not, break student list into left and right halves

			int middle = (end + begin) /2;
			//call mergeSort on the halves, which are now sorted
			mergeSort(studentList, begin, middle);
			mergeSort(studentList, middle + 1, end);
			vector<Student> temp; //this holds the intermediate sort results
			int firstIter = begin, secondIter = middle + 1;
			//merge the return values
			while ( firstIter <= middle && secondIter <= end){
				if (comp(studentList[firstIter] , studentList[secondIter])){ 
		 			temp.push_back(studentList[firstIter]);
		 			++firstIter;
				}
		 		else {
		 			temp.push_back(studentList[secondIter]);
					++secondIter;
		 		}
			}

			while (firstIter <= middle){
				temp.push_back(studentList[firstIter]);
				++firstIter;
			}
	
			while (secondIter <= end){
				temp.push_back(studentList[firstIter]);
				++secondIter;
			}
			////update the vector with the sorted elements from temp
			for (int i = begin, j = 0; i <= end; i++,j++){
				studentList[i] = temp[j];
			}	

	}

	public:
		void sort(vector<Student>& students){
			mergeSort(students, 0, students.size()-1);
		}
	bool (*comp)(Student x, Student y) = Student::comparator;


};


int main(){
	//initialize students and a list, populate the list
	Student std1 = {"0001", 80};
	Student std2 = {"0002", 90};
	Student std3 = {"0003", 75};
	Student std4 = {"0004", 63};
	Student std5 = {"0005", 88};
	//assert(Student::comparator(std1,std2));
	vector<Student> studentList;
	studentList.push_back(std1);
	studentList.push_back(std2);
	studentList.push_back(std3);
	studentList.push_back(std4);
	studentList.push_back(std5);
	//sort the list using the comparator
	MergeSort sorter;
	sorter.sort(studentList);	
	//make sure the list is sorted
	for (Student s : studentList){
		cout << s.studentID << " : " << s.score << endl;
	}
}
