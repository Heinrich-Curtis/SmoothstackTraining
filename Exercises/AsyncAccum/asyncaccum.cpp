//uses an async task and the std::accumulate algorithm to sum up a bunch of stuff
//in parallel

/*
	Interesting bug getting this to work: I wasn't specifying a type to std::accumulate inside of parallel_sum, I was just using the immediate 0.
	Because of this, std::accumulate was returning some type too small to hold the actual sum, and I was overflowing that type resulting in an
	incorrect accumulation, and bizarrely, the parallel version of the algorithm was ALWAYS slower than the single-threaded version. Note that 
	I had -Wall and -Werror  switches on my compilation and never got any warnings, although technically there was no narrowing since 
	std::accumulate inferred my type was a short based on the argument I supplied it. As soon as I made the type explicit, the result is now
	correct AND the parallel version now ALWAYS runs faster than the single-threaded version.
*/


#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <future>
#include <cassert>
#include <thread>
//here's the thread that does the summing on iterators


template <typename It>
unsigned long long parallel_sum(It begin,It end){
	//just do accumulate on these things
	unsigned long long res = 0;
	return std::accumulate(begin, end, res);
}

int main(){
	std::vector <unsigned long long> nums;
	for (unsigned int i = 0; i < 5000000; ++i){
		nums.push_back(i);
	}
	//find the midpoint
	unsigned int mid = nums.size()/2;
	//get an iterator to mid
	auto it = nums.begin();
	std::advance(it, mid);
	//now we set one part as the back end in a task, and one part as the front end here
	auto start = std::chrono::steady_clock::now();
	//note how we need to specify the specialization of vector so we can use the iterator here
	auto handle = std::async(std::launch::async,parallel_sum<std::vector<unsigned long long>::iterator>, nums.begin(), it);
	unsigned long long sum = parallel_sum(it,nums.end());
	unsigned long long res = sum + handle.get();
	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed = end - start;
	std::cout<< "parallel time is "<<elapsed.count()<<std::endl;
	std::cout <<"res is "<<res<<std::endl;
	//last compare to the sequential accumulate for accuracy
	start = std::chrono::steady_clock::now();
	unsigned long long res2 = parallel_sum(nums.begin(), nums.end());
	end = std::chrono::steady_clock::now();
	elapsed = end - start;
	std::cout<<"single threaded time is "<<elapsed.count()<<std::endl;
	std::cout <<"res2 is "<<res2<<std::endl;
	assert (res2 == res); 
	return 0;
}
