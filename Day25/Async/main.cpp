/*
    Program that implmeents a parallel accumulate and an async accumulate
    using std::promise. This is mostly the code from the slides, modified
    slightly by me to use promise and future.
*/
#include <future>
#include <thread>
#include <chrono>
#include <cassert>
#include <numeric>
#include <array>
#include <iostream>
#include <vector>

//parallel accumulate using promise
template<typename Iterator,typename T> 
struct accumulate_block {
    T operator()(Iterator first, Iterator last) {
        T res = std::accumulate(first, last, T());
        return res;
    }
};

//need a method that sums the promises for the final result
template<typename T>
T sum_futures(std::vector<std::future<T>>& vec){
    T result = T{};
    for (std::future<T>& p : vec){
        result += p.get();
    }
    return result;
}

template<typename Iterator, typename T>
T async_accumulate(Iterator first, Iterator last, T init) {
    unsigned long const length=std::distance(first, last);
    if (!length)
        return init;
    unsigned long const min_per_thread = 25;
    unsigned long const max_threads = (length+min_per_thread-1)/min_per_thread;
    unsigned long const hardware_threads = std::thread::hardware_concurrency();
    unsigned long const num_threads = std::min(hardware_threads!=0?hardware_threads:2,max_threads);
    //std::cout << "num_threads: " << num_threads << std::endl;
    unsigned long const block_size = length/num_threads;
    std::vector<std::future<T>> results(num_threads);
    //std::vector<std::thread> threads(num_threads-1);
    Iterator block_start = first;
    for (unsigned long i = 0; i < (num_threads-1); ++i) {
        Iterator block_end = block_start;
        std::advance(block_end, block_size);
        //using threads here but the threads return promises?
        results[i]= std::async(std::launch::async, accumulate_block<Iterator,T>(), block_start, block_end);
        block_start = block_end;
    }
    //final accumulate
    results[num_threads-1] = std::async(std::launch::async, accumulate_block<Iterator,T>(), block_start, last);
    return sum_futures(results);

    /* No joins because no threads
    for (auto& entry: threads)
           entry.join();
    */

}

int main(){
    //create array and populate it
    std::array<int, 100000> arr;
    for (int i = 0; i < arr.size(); ++i){
        arr[i] = i;
    }
    //run async accumulate on it 
    auto res = async_accumulate(arr.begin(),arr.end(),(int)0);
    std::cout<< "Testing implmentations on the range 0 to 100000"<<std::endl;
    std::cout << "Result of my parallel accumulate: "<< res << std::endl;

    auto res2 = std::accumulate(arr.begin(), arr.end(), (int)0);
    std::cout << "Result of single thread accumulate: "<< res2 << std::endl;
    assert(res == res2);
    return 0;
}
