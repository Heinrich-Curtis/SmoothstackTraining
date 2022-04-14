/*
    Program that demonstrates the effects of different memory
    access patterns on atmoic variables in a multi-threaded  program
*/

#include <thread>
#include <atomic>
#include <iostream>
#include <array>
#include <cassert>

//some shared atomic values
std::atomic<int> x = 1;
std::atomic<int> y = 2;

void storeX(){
x.store(3);
}

void storeY(){
y.store(4);
}

void readXreadY(std::memory_order order){
x.load(order);
//use compare functions?
y.load(order);
}

void readYreadX(std::memory_order order){
y.load(order);
x.load(order);
}

int main(){
   /*
    if (std::atomic<int>::is_always_lock_free){
        std::cout << "Ints are always lock-free" << std::endl;
    }
    */
    //make an array of threads and populate it
    std::array<std::thread,4> arr = {};
    std::thread t1(storeX);
    arr[0] = std::move(t1);
    t1 = std::thread(storeY);
    arr[1] = std::move(t1);
    t1 = std::thread(readXreadY, std::memory_order_seq_cst);
    arr[2] = std::move(t1);
    t1 = std::thread(readYreadX, std::memory_order_seq_cst);
    arr[3] = std::move(t1);
    //join everyone on the way out
    for (int i = 0; i < 4; ++i){
        arr[i].join();
    }

    return 0;
}