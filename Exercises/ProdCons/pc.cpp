//program where one thread produces items and puts them in a vector
//and the other thread consumes the items
#include <thread>
#include <iostream>
#include <vector>
#include <string>
#include <pthread.h>
#include <semaphore.h>
#include <cassert>
#include <set>
#include <condition_variable>

//sync device
sem_t sync;
sem_t sync2;
bool processed;
//a templated version of consumer
template <typename Cont>
void consume(Cont cont, sem_t& sem){
	for (int i =0; i < 5; ++i){
		sem_wait(&sem);
		auto s = cont.begin(); //as long as these operations are valid for Cont, we're good
		std::cout << *s << std::endl;
		cont.erase(cont.begin());
	}
}

bool ready = false;
//consumer uses a condition variable instead
void consumer(std::vector<std::string>& vec,std::mutex& mut, std::condition_variable& cv){
	std::unique_lock<std::mutex> lk(mut);
	cv.wait(lk, []{return ready;});//needs to be a unique_lock
	for (const auto& s : vec){
		std::cout << s << std::endl;
	}
	mut.unlock();
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
	//give the cv a lock
	std::mutex mut3;
	std::condition_variable cv;
	sem_init(&sync,0,0);
	sem_init(&sync2,0,0);
	std::vector<std::string> myVec;
	std::set<std::string> mySet;
	std::thread t(consume<std::vector<std::string>>,std::ref(myVec),std::ref(sync)); //if I pass in a templated type, I have to pass in it's template instantiation as well
	std::this_thread::yield();
	std::string arr[] = {"one","two","three","four","five"};
	for (int i = 0; i < 5; ++i){//this is dangerous, the semaphore doesn't mean that only one thread accesses the structure at a time
		myVec.push_back(arr[i]);
		sem_post(&sync);
	}
	for(int i=0; i < 5; ++i){
		mySet.insert(arr[i]);//insert seems to put them in backwards
		sem_post(&sync2);
	}
	//now run a thread that drains it
	std::thread t2(consume<std::set<std::string>>,std::ref(mySet),std::ref(sync2));
	//t should complete naturally
	//t2 should also complete fine
	t.join();
	t2.join();
	//use consumer
	std::thread t3(consumer,std::ref(myVec),std::ref(mut3),std::ref(cv));
	//populate the vector again and ring the bell
	std::unique_lock<std::mutex> lk(mut3);
	for (int i = 0; i < 5; ++i){
		myVec.push_back(arr[i]);
	}
	ready = true;
	cv.notify_one();
	lk.unlock();
	t3.join();
	//make a thing object
	thing thin(2);
	//if we want to use a non-static member function, the first thing is always a pointer to the object we're calling on
	std::thread th(&thing::plus_x,&thin,5);
	th.join();
	assert(thin.x == 2);
}
