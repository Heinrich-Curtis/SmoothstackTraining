/*
 * This header file holds all the miscellaneous definitions for this assignment
 */
#ifndef COUNTRIES_H
#define COUNTRIES_H
#include <iostream>
#include <thread>
#include <mutex>

//enum that specifies different currencies
enum class Currency{
    DOLLARS = 0,
    POUNDS = 1
};
//action type for requests
enum class Action{
    BUY = 0,
    SELL = 1
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
    //wonder if I need the other constructors/operators here

}Request;
//country
typedef struct Country{
    //base currency
    const Currency baseCurrency;
    Amount reserveCurrency;
    Amount forexCurrency;
    std::mutex lock;

    Country(Currency cur,Amount reserves, Amount forex): baseCurrency(cur),
    reserveCurrency(reserves),forexCurrency(forex){

    }
    //post a request to exchange to another country and wait for their response
    void makeRequest(Country* other){
        //to make a request, we lock both country's locks to signify
        //an outstanding request and then we put the request in their
        
    }
    //check if there is enough money to service a request
    bool haveEnoughMoney(Request& req){

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

    //function that runs in the thread that simulates trades
    void simulateTrade(Country* other, int numTrades){
        for (int i = 0; i < numTrades; ++i){
            //make a request to the other country and get response
            //adjust currencies accordingly
        }
    }
}Country;

#endif