/* program that demonstrates a deadlock condition when attempting
 * inter-thread communication.
 */
#include <iostream>
#include <thread>
#include "Countries.h"

int main(){
    //build two countries with each other as partners
    Country count1(Currency::DOLLARS,Amount(Currency::DOLLARS,1000.00),
     Amount(Currency::POUNDS,1000.00),nullptr);
    Country count2(Currency::POUNDS,Amount(Currency::POUNDS,1000.00),
     Amount(Currency::DOLLARS,1000.00),&count1);
     count1.setPartner(&count1);
    //run their threads
    std::thread t(&Country::simulateTrade,std::ref(count1));
    std::thread t2(&Country::simulateTrade,std::ref(count2));
    //try to join, but we never get here because we're deadlocked
    t.join();
    t2.join();
    return 0;
}