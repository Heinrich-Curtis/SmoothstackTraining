//create a deadlock using two threads, a mutex and a condition variable
#include <thread>
#include <mutex>

//sync stuff
std::mutex mut;
std::mutex mut2;
//function for thread locks a lock and signals a condition variable so
//the other thread can go
void threadFunc(){
	mut2.lock();
	mut.lock();
	mut2.unlock();
}

int main(){
	mut.lock();
	std::thread t(threadFunc);
	std::this_thread::yield();
	mut2.lock();
	mut.unlock();
	//mut.unlock();
	//no copyting or assigning
	//const std::mutex mut3 = std::move(mut);
	//can't lock a const mutex
	//const std::mutex mut3;
	//mut3.lock();
	t.join();
	return 0;
}
