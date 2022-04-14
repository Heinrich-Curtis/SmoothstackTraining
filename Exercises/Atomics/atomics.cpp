//using an atmoic to synchronize and force ordering on a number of threads
#include <iostream>
#include <thread>
#include <atomic>

//an atomic that syncs everyone
std::atomic<int> atom;

//functions that get synced
void funcOne(){
	while(atom.load() != 1){}
	std::cout<<"one"<<std::endl;
	atom.store(2); 
}

void funcTwo(){
	//spin lock essentially
	while(atom.load() != 2){}
	std::cout<<"two"<<std::endl;
	atom.store(3);
}

void funThree(){
	while(atom.load() != 3){}
	std::cout<<"three"<<std::endl;
}

int main(){
	atom.store(1);
	std::thread t2(funcTwo);
	std::thread t1(funThree);
	std::thread t3(funcOne);
	t1.join();
	t2.join();
	t3.join();
	return 0;
}
