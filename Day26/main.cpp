/*Program that implements a parallel version of std::any_of and an async version
 * of std::none_of
 */
#include <thread>
#include <iostream>
#include <future>
#include <cassert>
#include <vector>
#include <random>

// some predicate functions
bool lessThan25000(int i){
    return i <25000;
}

bool moreThan250000(int i){
    return i > 25000;
}

bool isLetterA(char c){
    return c == 'a';
}

//worker thread function for any_of
template<typename Iterator, typename UnaryPred>
void anyOfWorker(Iterator first, Iterator last, bool& flag, UnaryPred up){
    for (;first!=last;++first){
        if (flag) return;
        if(up(*first)){ //I don't think I need a mutex for this since there
                       //is only one type of change that will be made to flag 
            flag = true;
        }
    }
}
//parallel any_of
template<typename Iterator, typename UnaryPred>
bool pAnyOf(Iterator first, Iterator last, UnaryPred uP){
    //find the number of elements
    int numElements = std::distance(first,last);
    //figure out how many threads
    //I dunno how many elements per thread is good: 250?
    int blockSize = 250;
    int numThreads = (numElements / blockSize);
    Iterator start = first;
    //assign a flag value
    bool flag = false;
    //spin up the threads with the args and the flag value
    std::vector<std::thread> threads;
    for (int i = 0; i < numThreads; ++i){
        Iterator end = start;
        std::advance(end, blockSize);
        threads.push_back(std::thread(anyOfWorker<Iterator,UnaryPred>,std::ref(start),std::ref(end),std::ref(flag),uP));
        start = end;
    }
    //need to check the straggler batch, "I" do this part
    anyOfWorker(start,last,flag,uP);
    //join all the threads
    for (int i = 0;i < numThreads; ++i){
        threads[i].join();
    }
    //return the result
    return flag;
}

//async none_of worker
template <typename Iterator, typename UnaryPred>
bool noneOfWorker(Iterator first, Iterator last, bool& flag, UnaryPred up){
     for (;first!=last;++first){
        if (!flag) return false;
        if(up(*first)){ //I don't think I need a mutex for this since there
                       //is only one type of change that will be made to flag 
            flag = false;
        }
    }
    return true;
}
//async none_of
template <typename Iterator, typename UnaryPred>
bool aNoneOf(Iterator first, Iterator last, UnaryPred up){
 //find the number of elements
    int numElements = std::distance(first,last);
    //figure out how many threads
    //I dunno how many elements per thread is good: 250?
    int blockSize = 250;
    int numThreads = (numElements / blockSize);
    Iterator start = first;
    //assign a flag value
    bool flag = true;
    //spin up the threads with the args and the flag value
    std::vector<std::future<bool>> futs(numThreads);
    for (int i = 0; i < numThreads; ++i){
        Iterator end = start;
        std::advance(end, blockSize);
        futs[i] = std::async(noneOfWorker<Iterator,UnaryPred>,std::ref(start),std::ref(end),std::ref(flag),up);
        start = end;
    }
    //need to check the straggler batch, "I" do this part
    bool b = noneOfWorker(start,last,flag,up);
    if (!b) return false;
    for(std::future<bool>& fut : futs){
        if (!fut.get()) return false;
    }
    return true;

}

//main
int main(){
    srand(time(NULL));
    //populate some data for us to work with
    std::vector<int> vint;
    for (int i = 0; i < 24999; ++i){
        vint.push_back(i);
    }

    std::vector<char> vchar;
    for (int i = 0; i < 225; ++i){
        char c = i % 128;
        vchar.push_back(c);
    }

    //run functions on vint
    assert(pAnyOf(vint.begin(),vint.end(),lessThan25000));
    assert(!pAnyOf(vint.begin(),vint.end(),moreThan250000));
    assert(!aNoneOf(vint.begin(),vint.end(),lessThan25000));
    assert(aNoneOf(vint.begin(),vint.end(),moreThan250000));

    //run functions on vchar
    assert(pAnyOf(vchar.begin(),vchar.end(),isLetterA));
    assert(!aNoneOf(vchar.begin(),vchar.end(),isLetterA));

    
    return 0;
}