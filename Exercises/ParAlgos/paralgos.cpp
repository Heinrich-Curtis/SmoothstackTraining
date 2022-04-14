//stuff a  list with a shitload of values, sort it single-thread,
//then sort it parallel and compare the tims
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <chrono>
#include <execution>

int main(){
	std::vector<long long> myList;
	for (int i = 50000000; i >= 0; --i){
		myList.push_back(i);
	}
	//make a copy to sort in parallel
	std::vector<long long> myList2 = myList;
	//sort the first list
	auto start = std::chrono::steady_clock::now();
	std::sort(myList.begin(),myList.end());
	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	std::cout << "single-thread sort took "<< elapsed_seconds.count() <<"s"<<std::endl;

	//now do it with parallel
	start = std::chrono::steady_clock::now();
	std::sort(std::execution::par,myList2.begin(),myList2.end());
	end = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed_seconds2 = end - start;
	std::cout <<"Parallel sort took "<< elapsed_seconds2.count() <<"s"<<std::endl;
	std::cout <<"That's a speedup of  " << elapsed_seconds.count()/elapsed_seconds2.count() 
	 <<std::endl;
}

//the parallel version ALWAYS takes longer than the sequential version, I wonder why?

