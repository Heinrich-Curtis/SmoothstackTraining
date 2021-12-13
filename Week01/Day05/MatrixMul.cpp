/*
 * Program that takes 4 ints as the dimenstions of 2 matrices, allocates
 * the matrices, populates them with data randomly, then performs matrix
 * multiplication (if possible) and prints all 3 matrices to the terminal.
 *
 * The one bug I haven't worked on is recognizing when an input is invalid
 * (for instance, entering one of the input values as some string or the 
 * character 'a'. This cause all the prompts to show up and the program
 * terminates.
 */
#include <iostream>
#include <cassert>
#include <stdlib.h> //for exit and rand
#include <time.h> //getting a random seed from the time
#include <array>
#include <string.h>
#define MATRIX_ENTRY_MAX 1000 //arbitrary max to avoid overflow issues

using namespace std;
int main (){
	//get a seed for RNG
	srand(time(NULL));

	//get the user input for the dimensions of A and B and validate it
	int num;	
	cout << "Enter the number of rows in matrix A: ";
	cin >> num;
	if (num < 0) {
		cout << "The number of rows must be a positive integer."<< endl;
		exit(0);
	}
	const int rowsA = num;
	cout << "Enter the number of columns in matrix A: ";
	cin >> num;
	if (num < 0) {
		cout << "The number of columns must be a positive integer."<< endl;
		exit(0);
	}
	const int colsA = num;
	cout << "Enter the number of rows in matrix B: ";
	cin >> num;
	if (num < 0) {
		cout << "The number of rows must be a positive integer."<< endl;
		exit(0);
	} else if (num != colsA){
		cout << "The matrix product AxB is not defined if the " <<
			"number of rows in B is not equal to the number of " <<
			"columns in A." << endl;
		exit(0);
	}
	const int rowsB = num;
	cout << "Enter the number of columns in matrix B: ";
	cin >> num;
	if (num < 0) {
		cout << "The number of columns must be a positive integer." << endl;
		exit(0);
	}
	const int colsB = num;
	
	//now that we have the size of two matrices for which the product is 
	//defined, allocate space for all 3 (the size of C is already known)
	//and fill A and B with random data
	int A[rowsA][colsA];
	int B[rowsB][colsB];
	int C[rowsA][colsB];
	//clear C so we can just add to it when populating it
	memset(C, 0, sizeof(C[0][0])*rowsA*colsB);
	
	
	//populate A
	for (int i = 0; i < rowsA; i++){
		for (int j = 0; j < colsA; j++){
		//check which is slower: inner row or inner column
			A[i][j] = rand() % MATRIX_ENTRY_MAX;
		}	
	}
	
	//populate B
	for (int i = 0; i < rowsB; i++){
		for (int j = 0; j < colsB; j++){
			B[i][j] = rand() % MATRIX_ENTRY_MAX;
		}	
	}	
	
	//populate C
	for (int i = 0; i < rowsA; i++){
		for (int j = 0; j < colsB; j++){
			for (int k = 0; k < colsA; k++){
			C[i][j] += A[i][k]*B[k][j];
			}
		}
	}


	//print out the matrices
	cout << "Matrices: "<< endl;
	cout << "A: "<< endl;
	for ( int row = 0; row < rowsA; row++){
		for (int col = 0; col < colsA; col++){
			cout << A[row][col] << (col == colsA-1 ? "\n" : " ");
		}
	}
	
	cout << "B: "<< endl;
	for ( int row = 0; row < rowsB; row++){
		for (int col = 0; col < colsB; col++){
			cout << B[row][col] << (col == colsB-1 ? "\n" : " ");
		}
	}
	
	cout << "C: "<< endl;
	for ( int row = 0; row < rowsA; row++){
		for (int col = 0; col < colsB; col++){
			cout << C[row][col] << (col == colsB-1 ? "\n" : " ");
		}
	}

	return 0;
}

