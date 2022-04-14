//program where one thread produces items and puts them in a vector
//and the other thread consumes the items
#include <thread>
#include <iostream>
#include <vector>
#include <string>
#include <pthread.h>
#include <semaphore.h>
#include <cassert>

//sync device
sem_t sync;

template <typename Cont>
void consume(Cont cont){
	for (int i =0; i < 5; ++i){
		sem_wait(&sync);
		std::string s = cont.front(); //as long as these operations are valid for Cont, we're good
		cont.erase(cont.begin());
		std::cout << s << std::endl;
	}
}

//consumer
void consumer(std::vector<std::string>& vec){
	for (int i = 0; i < 5; ++i){
		sem_wait(&sync);
		std::string s = vec.front();
		vec.erase(vec.begin());
		std::cout << s << std::endl;
	}
}

struct thing{
	int x;
	thing(int y = 0): x(y){}//empty becase of initializer list
	int plus_x(int y){
		return x + y;
	}
	void set_x(int newx){
		x = newx;
	}
};

//producer
int main(){
	sem_init(&sync,0,0);
	std::vector<std::string> myVec;
	std::thread t(consume<std::vector<std::string>>,std::ref(myVec)); //if I pass in a templated type, I have to pass in it's template instantiation as well
	std::this_thread::yield();
	std::string arr[] = {"one","two","three","four","five"};
	for (int i = 0; i < 5; ++i){//this is dangerous, the semaphore doesn't mean that only one thread accesses the structure at a time
		myVec.push_back(arr[i]);
		sem_post(&sync);
	}
	//t should complete naturally
	t.join();

	//make a thing object
	thing thin(2);
	std::thread th(&thing::plus_x,&thin,5);
	th.join();
	assert(thin.x == 2);
}
