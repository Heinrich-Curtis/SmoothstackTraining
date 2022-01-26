/*
 * This header file holds all the miscellaneous definitions for this assignment
 */
#ifndef COUNTRIES_H
#define COUNTRIES_H
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

//enum that specifies different currencies
enum class Currency{
    DOLLARS = 0,
    POUNDS = 1
};
//action type for requests
enum class Action{
    IDLE = 0,
    BUY = 1,
    SELL = 2
};

enum class State{
    IDLE = 0,
    ACCEPTED = 1,
    REJECTED = 2
};

//type that encapsulates an amount of a specific currency
typedef struct Amount{
    Currency type;
    double amount;

    Amount(){
        type = Currency::DOLLARS;
        amount = 0.00;
    }
    Amount(Currency cur, double count): type(cur),amount(count){
        //blank
    };
    //CC
    Amount(Amount& other){
        type = other.type;
        amount = other.amount;
    }
    //CAO
    Amount& operator=(const Amount& other){
        if (this == &other){
            return *this;
        }
        type = other.type;
        amount = other.amount;
        return *this;
    }
    //default MC/MAO is fine
    //default destructor is fine
}Amount;
//type that encapsulates a request for trading currency
typedef struct Request{
    double exchangeRate;
    Amount cur;
    Action action;

    Request(double rate, Amount cur, Action act): exchangeRate(rate),
    cur(cur), action(act){
        //blank
    }
    Request(){
        exchangeRate = 0.00; 
        cur = Amount();
        action = Action::IDLE;

    }
    Request(Request& req){
        this->exchangeRate = req.exchangeRate;
        this->cur = req.cur;
        this->action = req.action;
    }
    //wonder if I need the other constructors/operators here

}Request;
//country
typedef struct Country{
    //base currency
    const Currency baseCurrency;
    Amount reserveCurrency;
    Amount forexCurrency;
    std::mutex mut;
    State state;
    Country* tradePartner;
    //this holds all the data when we make a request
    Request req;

    Country(Currency cur,Amount reserves, Amount forex, Country* partner):
     baseCurrency(cur),reserveCurrency(reserves),forexCurrency(forex), 
     tradePartner(partner){

    }
    //configure my request fields in preparation for sending
    void buildRequest(Request& req){
        //set fields
        this->req = req;
        
    }

    //post a request to exchange to another country and wait for their response
    void makeRequest(Country* other){
        //to make a request, we lock our lock and then their lock. Doing
        //this causes a deadlock becasue now the other thread can't even poll.
        mut.lock();
        other->mut.lock();
        
    }
    //check if there is enough money to service a request
    bool haveEnoughMoney(Request& req){
        return true;
    }

    /*
     * method to adjust internal amounts based on an accepted trade. Remember
     * the request is from the perspective of the other country. So if the 
     * action is "BUY", that means we are selling (getting rid of our
     * currency for the other one)
     */
    void processAcceptedTrade(const Request& req){
        if (req.action == Action::BUY){

        }
    }
    //this method allows the country to wake up, and check it's state. If 
    //anything is going on, we do stuff. If nothing is going on, we go back to
    //sleep
    //maybe this return a value to signify a trade was completed in the poll
    int poll(){
        //lock 
        mut.lock();
        //check status and partner pointer
        if (state == State::IDLE && tradePartner == nullptr){
            mut.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            return 0;
        }
        else if (state == State::IDLE && tradePartner != nullptr){
            //check the offer
            //make a decision
            //adjust members accordingly
            return 1;
        }
        return 2;
    }

    //function that runs in the thread that simulates trades
    void simulateTrade(){
        int sendCount = 0;
        int recCount = 0;
        Request req1(0.5, Amount(), Action::SELL);
        Request req2(0.5, Amount(Currency::DOLLARS,10.00), Action::BUY);
        //we deadlock here becasue both countries try to grab both locks
        makeRequest(tradePartner);
        while(sendCount < 2 || recCount < 2){
            //make 2 requests, then poll until we hit the recCount
            int res = poll();
            if(res == 1) sendCount++;
            else if (res == 2) recCount++;
        }
        //we've done the requests so we're done
    }

    void setPartner(Country* other){
        this->tradePartner = other;
    }
}Country;

#endif