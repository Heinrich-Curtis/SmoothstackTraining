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
    void operator()(Iterator first, Iterator last, std::promise<T>& result) {
        T res = std::accumulate(first, last, T());
        result.set_value(res);
    }
};

//need a method that sums the promises for the final result
template<typename T>
T sum_promises(std::vector<std::promise<T>>& vec){
    T result = T();
    for (std::promise<T>& p : vec){
        result += p.get_future().get();
    }
    return result;
}

template<typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init) {
    unsigned long const length=std::distance(first, last);
    if (!length)
        return init;
    unsigned long const min_per_thread = 25;
    unsigned long const max_threads = (length+min_per_thread-1)/min_per_thread;
    unsigned long const hardware_threads = std::thread::hardware_concurrency();
    unsigned long const num_threads = std::min(hardware_threads!=0?hardware_threads:2,max_threads);
    //std::cout << "num_threads: " << num_threads << std::endl;
    unsigned long const block_size = length/num_threads;
    std::vector<std::promise<T>> results(num_threads);
    std::vector<std::thread> threads(num_threads-1);
    Iterator block_start = first;
    for (unsigned long i = 0; i < (num_threads-1); ++i) {
        Iterator block_end = block_start;
        std::advance(block_end, block_size);
        //using threads here but the threads return promises?
        threads[i] = std::thread(accumulate_block<Iterator,T>(), block_start, block_end,std::ref(results[i]));
        block_start = block_end;
    }
    accumulate_block<Iterator,T>() (block_start, last, results[num_threads-1]);
    for (auto& entry: threads)
           entry.join();
    return sum_promises(results);
    //instead of this, accumulate the results of the promises
    //return std::accumulate(results.begin(), results.end(), init);
}
//async accumulate using promise

int main(){
    //create array and populate it
    std::array<int, 100> arr;
    for (int i = 0; i < arr.size(); ++i){
        arr[i] = i;
    }
    //run parallel accumulate on it 
    auto res = parallel_accumulate(arr.begin(),arr.end(),(int)0);
    std::cout << "Result of my parallel accumulate: "<< res << std::endl;
    //run async accumulate on it
    //auto res2 = async_accumulate(arr.begin(), arr.end(), (int)0);
    //std::cout << "Result of async accumulate: "<< res << std::endl;
    //compare to the reference version of accumulate
    auto res3 = std::accumulate(arr.begin(), arr.end(), (int)0);
    std::cout << "Result of single thread accumulate: "<< res3 << std::endl;
    //assert(res/* == res2 */== res3);
    return 0;
}

/*
//test accumulate
void testAccumulate(){
    std::array<int,100> arr{0};
    for (int i = 0; i < arr.size(); ++i){
        arr[i] = i;
    }
    auto res = std::accumulate(arr.begin(),arr.end(),(int)0);
    std::cout<<"accumulate from 0 to 100 with init 0: "<<res<<std::endl;
    res = std::accumulate(arr.begin(),arr.end(),(int) 1);
    std::cout<<"accumulate from 0 to 100 with init 0: "<<res<<std::endl;
}
*/