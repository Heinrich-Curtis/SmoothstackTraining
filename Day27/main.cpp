/*
 *	Program that performs parallel matrix multiplication using openMP
 */
#include <iostream>
#include <thread>
#include <omp.h>
#include <vector>
#include <cassert>
#include <string.h>

//need a matrix type here
template<typename T>
struct Matrix{
		int rows;
		int cols;
		T** data; //flat representation of the matrix entries
		Matrix(): rows(0),cols(0),data(nullptr){}
		
		//empty matrix of appropriate size
		Matrix(int rowNum, int colNum): rows(rowNum), cols(colNum){
			if (rows < 1 || cols < 1){
				data = nullptr;
			}
			else{
				data = new T*[rows];
				for (int i = 0; i < rows; ++i){
					data[i] = new T[cols];
				}
			}
		}
		
		//take data and turn it into a matrix
		Matrix(T* newData, int rowNum, int colNum): rows(rowNum), cols(colNum){
			if (rows < 1 || cols < 1){
				data = nullptr;
				return;
			}
			data = new T*[rows];
			for (int r = 0; r < rows;++r){
				data[r] = new T[cols];
				for (int c = 0; c < cols;++c){
					data[r][c] = newData[(r*cols) + c];
				}
			}
		}
		
		//CC
		Matrix(const Matrix& other){
			rows = other.rows;
			cols = other.cols;
			if (rows == 0 || cols == 0){
				data = nullptr;
				return;
			}
			data = new T*[rows];
			for (int r = 0; r < rows;++r){
				data[r] = new T[cols];
				for (int c = 0; c < cols;++c){
					data[r][c] = other.data[(r*cols) + c];
				}
			}
		}
		
		//MC
		Matrix(Matrix<T>&& other){
			rows = other.rows;
			cols = other.cols;
			data = other.data;
			other.data = nullptr;
			other.rows = 0;
			other.cols = 0;	
		}

		//CAO
		Matrix& operator=(const Matrix& other){
			if (this == &other) return *this;
			if (data != nullptr){
				delete[] data;
			}
			rows = other.rows;
			cols = other.cols;
			data = new T*[rows];
			for (int r = 0; r < rows;++r){
				data[r]= new T[cols];
				for (int c = 0; c < cols;++c){
					data[r][c] = other.data[(r*cols) + c];
				}
			}
			return *this;
		}
		//MAO
		Matrix& operator=(Matrix&& other){
			if (this == &other) return *this;
			if (data != nullptr){
				delete[] data;
			}
			rows = other.rows;
			cols = other.cols;
			data = other.data;
			other.data = nullptr;
			other.rows = 0;
			other.cols = 0;
			return *this;
		}


		~Matrix(){ //delete the dynamic memory
			if (data != nullptr){
				for (int i = 0; i < rows; ++i){
					delete[] data[i];
				}
				delete[] data;
			}
		}

		void print(){
			std::cout<<"Matrix:"<<std::endl;
			for (int r = 0; r < rows; ++r){
				for (int c = 0; c < cols; ++c){
					std::cout<<data[r][c];
					(c != cols - 1)?std::cout<<", " : std::cout<<std::endl;
				}
			}
		}
		//initialize the memory to 0
		void clear(){
			for (int r = 0; r < rows; ++r){
				for (int c = 0; c < cols; ++c){
					data[r][c] = 0;
				}
			}
		}
	//templated function that does matrix multiplication on 2 flattened 
	//matrices
	
	Matrix<T> multiply(const Matrix<T>& other){
		//make sure the multiplication is possible. If it isn't, return a null
		//matrix
		Matrix<T> result = Matrix<T>(rows,other.cols);
		if (cols != other.rows) return result;
		result.clear();
		auto numThreads = std::thread::hardware_concurrency();
		//std::cout<<"Multiplying with as many as "<<numThreads<<" threads" <<
		// std::endl;
		//initialization of private variables
		int i =0, j=0, k=0, iOff=0, jOff=0/*, dimension = rows*/;
		T tot;
		//flatten the matrices here
		/*
		T flattenA[rows*cols];
		T flattenB[other.rows * other.cols];
		for (int r = 0; r < rows;++r){
			for (int c = 0; c < cols; ++c){
				flattenA[r*cols + c] = data[r][c];
			}
		}
		for (int r = 0; r < other.rows; ++r){
			for (int c = 0; c < other.cols;++c){
				flattenB[r*other.cols + c] = other.data[r][c];
			}
		}
		*/
		#pragma omp parallel shared(result) private(i,j,k,iOff,jOff,tot) num_threads(numThreads)
		{
		  #pragma omp for schedule(static)
			/*
			for (i = 0;  i < dimension; i++) {
				iOff = i * dimension;
				for (j = 0; j < dimension; j++) {
					jOff = j * dimension;
					tot = 0;
					for (k = 0; k < dimension; k++) {
						tot += flattenA[iOff + k] * flattenB[jOff + k]; //this second term here is wrong
					}
					result.data[i][j] = tot;
				}
			}
			*/
			for (int i = 0; i < result.rows; i++) {
        		for(int j = 0; j < result.cols; j++) {
            		for(int k = 0; k < rows; k++) {
                		result.data[i][j] += data[i][k] * other.data[k][j];
					}
            	}
        	}
    	}
		return result;
	}
};

void testFunc(){
	Matrix<int> m;
	std::cout<<"Printing a blank matrix:"<<std::endl;
	m.print();
	int arr[] = {1,2,3,4};
	Matrix<int> m2(arr,2,2);
	std::cout<< "Printing a 2x2 matrix:"<<std::endl;
	m2.print();
	m = std::move(m2);
	assert(m2.data == nullptr);
	Matrix<int> m3(arr,2,2);
	std::cout<<"Result of squaring [[1,2],[3,4]] (multiplying it by itself): "<<std::endl;
	Matrix<int> m4 = m.multiply(m3);
	m4.print();
	//assert the product of two square matrices is correct
	assert(m4.data[0][0] == 7);
	assert(m4.data[0][1] == 10);
	assert(m4.data[1][0] == 15);
	assert(m4.data[1][1] == 22);
	int arr3[] = {1,2};
	Matrix<int> m5(arr3,2,1);
	Matrix<int> m6 = m3.multiply(m5);
	//assert the product of non-square matrices
	assert(m6.data[0][0] == 5);
	assert(m6.data[1][0] == 11);
	std::cout<<"Product of [[1,2],[3,4]] and [1,2] : "<<std::endl;
	m6.print();

}

int main(){
	/*
	omp_set_num_threads(4);
	#pragma omp parallel
	{
		std::cout << "Hello World" << std::endl;
	}*/
	testFunc();
	return 0;
}
