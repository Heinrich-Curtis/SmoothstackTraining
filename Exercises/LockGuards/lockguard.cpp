//use lock_guard and unique_lock
#include <thread>
#include <mutex>
#include <iostream>

std::mutex mut;
int i;
//lock the lock and adjust the member using unique lock
void critSection(){
	std::lock_guard<std::mutex> lock(mut);
	i += 3;
	std::cout<<"i is now "<<i<<std::endl;
}

//a type I can use unique_lock with
typedef struct Thing{
	std::mutex mut;
	int data;
	void transfer(Thing& thing1, Thing& thing2){
		//transfer the locks without locking
		std::unique_lock<std::mutex> l1(thing1.mut, std::defer_lock);
		std::unique_lock<std::mutex> l2(thing2.mut, std::defer_lock);
		//lock both at once and operate on boths data
		std::lock(l1,l2);
		thing1.data +=5;
		thing2.data -= 2;
		//unique locks are unlocked on their destruction when they lose scope
	}
}Thing;

int main(){
	//make some threads and have them run through the critical section,
	//there's no output scrambling because of the lock
	std::thread threads[5];
	for (int i = 0; i < 5; ++i){
		threads[i] = std::thread(critSection);
	}
	//now we join all the threads
	for (int i = 0; i < 5; ++i){
		threads[i].join();
	}

	//make some things to work on
	 Thing thing1, thing2;
	//start some threads 
	std::thread t1(Thing::transfer, &thing1, std::ref(thing1), std::ref(thing2));
	std::thread t2(Thing::transfer, &thing2, std::ref(thing1), std::ref(thing2));
	t1.join();
	t2.join();
	return 0;
}
