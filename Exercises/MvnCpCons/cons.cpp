//a simple type with the 5 constructors defined (default cons, copy cons,
//mv cons, CAO and MAO)
#include <iostream>
#include <cassert>
#include <memory> //unique_ptr
typedef struct thing{
	//dynamically allocated member
	int* arr;
	int arrSize;
	//default cons
	thing(){
		arrSize = 0;
		arr = nullptr;
	}
	//overloaded cons
	thing(int size){
		arrSize = size;
		arr = new int[arrSize];
	}
	//copy const
	thing(const thing& other){
		arrSize = other.arrSize; //get the other size
		if (other.arrSize == 0) {//if it's empty, be empty
			arr = nullptr;
		}
		else {
			arr = new int[arrSize];//make your own array
			for (int i = 0 ; i < arrSize; ++i){
				arr[i] = other.arr[i];//copy everything over
			}
		}
	}
	//mv const
	thing(thing&& other){
		arrSize = other.arrSize;//copy the size
		arr = other.arr;//take their data
		other.arr = nullptr;//set them to null
	}
	//CAO
	thing& operator=(const thing& other){
		if (arrSize != 0){//if I have data, delete it
			delete[] arr;
		}
		arrSize = other.arrSize;//copy their size
		if (arrSize == 0) arr = nullptr;//if their size is 0, be empty
		else{
			arr = new int[arrSize];
			for (int i = 0; i < arrSize; ++i){
				arr[i] = other.arr[i];//copy their data
			}
		}
		return *this;//always return a reference to this
	}
	//MAO
	thing& operator=(thing&& other){
		if (arrSize != 0){//if we have data, delete it
			delete[] arr;
		}
		arrSize = other.arrSize;//get their size
		arr = other.arr;//take their data
		other.arrSize = 0;//set them to empty
		other.arr = nullptr;
		return *this;//always return this
	}
	//destructor
	~thing(){
		if (arr != nullptr){//watch for the double free by checking
			delete[] arr;
		}
	}
}thing;


int main(){
	thing t1;
	//make a unique pointer from a raw one
	std::unique_ptr<int[]> up(new int[5]);
	assert(t1.arr == nullptr);
	thing t2(5);
	assert(t2.arr != nullptr);
	assert(t2.arrSize == 5);
	thing t3(t2);
	assert(t3.arr != nullptr);
	assert(t3.arr != t2.arr);
	assert(t3.arrSize == 5);
	thing t4;
	//copy assignement operator
	t4 = t3;
	assert(t4.arr != t3.arr);
	assert(t4.arrSize == 5);
	//move assignment operator
	t1 = std::move(t4);
	assert (t1.arr != nullptr);
	assert(t4.arr == nullptr);
	//move constructor
	int* oldArr = t1.arr;
	thing t5(std::move(t1));
	assert(t5.arr == oldArr);
	//rvalue references extend the life of temporaries
	int&& i = 5;
	assert(i == 5);
	assert(t1.arr == nullptr);
	return 0;
}
