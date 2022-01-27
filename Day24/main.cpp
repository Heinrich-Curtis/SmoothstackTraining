//Driver file the demonstrates use of the thread-safe queue
#include <iostream>
#include <queue>
#include "ThreadSafeQueue.h"
#include <cassert>
using namespace std;

//this thread pushes a bunch of stuff onto the queue
void pushingThread(ThreadSafeQueue<int>& t){
    for (int i = 0; i < 10; ++i){
        t.push(i);
    }
}
//this thread uses the try_pop reference version
void tryPoppingThread(ThreadSafeQueue<int>& t){
    //try popping an empty queue with the reference version
    int i;
    int b = t.try_pop(i);
    if (b){
        std::cout<<"Returned from TSQ: " << i << std::endl;
    }
    else{
        std::cout<<"queue was busy, could not pop"<<std::endl;
    }
    shared_ptr<int> ptr = t.try_pop();
    if (ptr){
    std::cout<<"Returned from TSQ: " << *ptr << std::endl;
    }
    else{
        std::cout<<"queue was busy, could not pop"<<std::endl;
    }
}
int main(){
    ThreadSafeQueue<int> tsq;
    assert(tsq.empty());
    std::thread t2(pushingThread,std::ref(tsq));
    std::thread t1(tryPoppingThread, std::ref(tsq));
    //sleep for a bit so we know the first half of tryPopping is done

    
    t1.join();
    t2.join();
    return 0;
}