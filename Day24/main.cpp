//Driver file the demonstrates use of the thread-safe queue
#include <iostream>
#include <queue>
#include "ThreadSafeQueue.h"
#include <cassert>
using namespace std;

//this thread pushes a bunch of stuff onto the queue
void pushingThread(ThreadSafeQueue<int>& t){
    for (int i = 0; i < 1000; ++i){
        t.push(i);
    }
}
//this thread uses the try_pop reference version
void tryPoppingThread(ThreadSafeQueue<int>& t){
    //try popping an empty queue with the reference version
    int i;
    bool b = t.try_pop(i);
    assert (!b);
    //try popping an empty queue with the pointer version
    std::shared_ptr<int> ptr = t.try_pop();
    assert(ptr == nullptr);
    //sleep for a while so the pushing thread can populate the queue
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    //now pop some values
    b = t.try_pop(i);
    assert(b);
    std::cout<<"Returned from TSQ: " << i << std::endl;
    ptr = t.try_pop();
    assert(ptr != nullptr);
    std::cout<<"Returned from TSQ: " << *ptr << std::endl;

}
int main(){
    ThreadSafeQueue<int> tsq;
    assert(tsq.empty());
    std::thread t1(tryPoppingThread, std::ref(tsq));
    //sleep for a bit so we know the first half of tryPopping is done
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::thread t2(pushingThread,std::ref(tsq));
    t1.join();
    t2.join();
    return 0;
}