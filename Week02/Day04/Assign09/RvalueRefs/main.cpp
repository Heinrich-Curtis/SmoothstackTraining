/*
 *	Program that demonstrates the use of rvalue references to print a grade
 */
#include <iostream>
#include <random>
#include <cstdlib>
#include <iomanip>
#include <cassert>

using namespace std;
//#define TEST
class Grade{
	private:
		char grades[6]  = {'F','D','C','B','A','A'};
	public:
		char grade(const int&& score){
			return grades[ score / 10 ];
		}
};

int main(){
	Grade gr;	
	#ifndef TEST

	//random seed
		srand(time(NULL));
	//populate array of scores, then print output
		int scores[4];
		for (int i = 0; i < 4; i++){
			scores[i] = rand() % 51;
			cout << "Score: " << setw(2) << scores[i] << ", Grade " 
				<< gr.grade(scores[i]+ 0) << endl;
		}
	#else
		//run tests
		assert(gr.grade(0) == 'F');
		assert(gr.grade(9) == 'F');
		assert(gr.grade(10) == 'D');
		assert(gr.grade(19) == 'D');
		assert(gr.grade(20) == 'C');
		assert(gr.grade(29) == 'C');
		assert(gr.grade(30) == 'B');
		assert(gr.grade(39) == 'B');
		assert(gr.grade(40) == 'A');
		assert(gr.grade(49) == 'A');
		assert(gr.grade(50) == 'A');
		cout << "All 11 tests passed" << endl;
		
	#endif	
		
	
}
