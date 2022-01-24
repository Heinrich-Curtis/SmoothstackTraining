/*
 *	A program that demonstrates a race condition by having 2
 *	threads attempt to update a shared data structure
 */
#include <vector>
#include <iostream>
#include <thread>
#include <mutex>
typedef struct sharedArr{
	std::mutex locker;
	uint64_t arr[250];
	int nextIndex = 0;

	uint64_t& operator[](int ind){
		return arr[ind];
	}

}sharedArr;
//populate vec with the values of the hailstone sequence 
uint64_t hailstone(uint64_t val){
	if (val % 2){
		return (val * 3) + 1;
	}
	else{
		return val / 2;
	}
}
//populate the vector with the hailstone sequence
void threadFunc(sharedArr& arr, uint64_t start){	
	while(true){
		arr.locker.lock();
		if (arr.nextIndex == 0){
			arr[0] = start;
			std::cout<<arr[arr.nextIndex] << " ";
			++arr.nextIndex;
			arr.locker.unlock();
		}
		else{	
			//terminating condition
			if (arr[arr.nextIndex-1] == 1){
				arr.locker.unlock();
				return;
			}	
			arr[arr.nextIndex] = hailstone(arr[arr.nextIndex-1]);
			std::cout<<arr[arr.nextIndex] << " ";
			++arr.nextIndex;
			arr.locker.unlock();
		}
	}
}

int main(int argc, char** argv){
	//get the start value from input
	uint64_t start = 0;
	sharedArr arr;
	start = atoi(argv[1]);
	std:: thread t(threadFunc,std::ref(arr), start);
	std::thread t2(threadFunc,std::ref(arr), start);
	std::thread t3(threadFunc,std::ref(arr), start);//join the threads and print the output
	t.join();
	t2.join();
	t3.join();
	std::cout<<std::endl;
	return 0;
}
