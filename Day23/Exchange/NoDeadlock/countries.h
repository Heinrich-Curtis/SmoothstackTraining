/*
 * This header file holds all the miscellaneous definitions for this assignment
 */
#ifndef COUNTRIES_H
#define COUNTRIES_H
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>

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
    PENDING = 1,
    ACCEPTED = 2,
    REJECTED = 3
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
    Request(double rate, Amount cur, Action act): exchangeRate(rate),
    cur(cur), action(act){
        //blank
    }

    void clear(){
        this->exchangeRate = 0.00;
        this->cur = Amount();
        this->action = Action::IDLE;
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
    void makeRequest(Country* other, Request& req){
        //to make a request, we lock our lock and then their lock. Doing
        //this causes a deadlock becasue now the other thread can't even poll.
        mut.lock();
        //set fields
        this->req = req;
        this->state = State::PENDING;
        //unlock my mutex
        mut.unlock();
        //lock the partner mutex
        tradePartner->mut.lock();
        //set their partner pointer
        tradePartner->tradePartner = this;
        //unlock partner mutex
        tradePartner->mut.unlock();
        //done 
    }
    //utility function to convert the amount of foreign currency
    //to an equivalent amount of our currency
    double convertCurrAmount(double exchRate,double forAmount){
        return forAmount * exchRate;
    }
    
    /*
     * method to adjust internal amounts based on an accepted trade. Remember
     * the request is from the perspective of the other country. So if the 
     * action is "BUY", that means we are selling (getting rid of our
     * currency for the other one)
     */
    
    void processMyAcceptedTrade(){
        //convert if necessary
        double amount = req.cur.amount;
        if (this->baseCurrency != req.cur.type){
            amount = convertCurrAmount(
                req.exchangeRate,req.cur.amount);
        }
        //we're buying, so they're selling
        if (req.action == Action::BUY){
            this->reserveCurrency.amount += amount;
            this->forexCurrency.amount -= req.cur.amount;
        }
        //we're selling, so they're buying
        else{
            this->reserveCurrency.amount -= req.cur.amount;
            this->forexCurrency.amount += amount; 
        }
    }

    //adjust our members
    void acceptTheirTrade(){
        //copy over their request so we don't need their lock
        tradePartner->mut.lock();
        Request requ = tradePartner->req;
        tradePartner->state = State::ACCEPTED;
        tradePartner->mut.unlock();
        double amount = requ.cur.amount;
        //convert their currency to ours
        if (this->baseCurrency != requ.cur.type){
            amount = convertCurrAmount(
                requ.exchangeRate,requ.cur.amount);
        }
        if (requ.action == Action::BUY){
            this->reserveCurrency.amount -= amount;
            this->forexCurrency.amount += requ.cur.amount;
        }
        //they're selling, so we're buying
        else{
            this->reserveCurrency.amount += requ.cur.amount;
            this->forexCurrency.amount -= amount; 
        }
    }

    void rejectTheirTrade(){
        //get their lock, reject their trade, unlock, set my members
        tradePartner->mut.lock();
        tradePartner->state = State::REJECTED;
        tradePartner->mut.unlock();
    }
    //arbitrarily decide whether to accept or reject an offer
    static bool doIAccept(){
        srand(time(nullptr));
        return rand() % 2;
    }

    //this method allows the country to wake up, and check it's state. If 
    //anything is going on, we do stuff. If nothing is going on, we go back to
    //sleep
    //maybe this return a value to signify a trade was completed in the poll
    int poll(){
        //lock 
        mut.lock();
        //check status and partner pointer
        //nothing happening, just waiting
        if (state == State::IDLE && tradePartner == nullptr){
            mut.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            return 0;
        }
        //there is an outstanding offer to us
        //I'm always going to prioritize an incoming trade rather than 
        //my own trade
        else if(tradePartner != nullptr){
            if (Country::doIAccept()){
                //accept their offer
                //reject their offer
                Country* partner = tradePartner;
                acceptTheirTrade();
                mut.unlock();
                partner->mut.lock();
                partner->state=State::ACCEPTED;
                partner->mut.unlock();
                std::cout<<"Thread "<<std::this_thread::get_id()<<
                 " accepts a trade"<<std::endl;
            }
            //reject their offer
            else{
                std::cout<<"Thread "<<std::this_thread::get_id()<<
                 " rejects a trade"<<std::endl;
                mut.unlock();
                rejectTheirTrade();
            }
            return 2;
        }
        //if we're rejected, clear the request field and change state
        //to idle, we're done
        else if (state == State::REJECTED){
            //clear our request
            this->req.clear();
            this->state = State::IDLE;
            //don't adjust any members, we got rejected
            //this technically counts as getting a response on an offer
        }
        //partner accepted our offer
        else if (state == State::ACCEPTED){
            //adjust our own members
            processMyAcceptedTrade();
        }
        //we're pending, waiting on them to make a decision on our offer
        
        else{   
            mut.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            return 0;
        }
        
        mut.unlock();
        return 2;
    }

    //function that runs in the thread that simulates trades
    void simulateTrade(){
        //Country* partner = tradePartner;
        int recCount = 0;
        Request req1(1.50, Amount(Currency::POUNDS,20.00), Action::SELL);
        Request req2(0.5, Amount(Currency::DOLLARS,10.00), Action::BUY);
        makeRequest(tradePartner,req1);
        while(recCount < 2){
            //make 2 requests, then poll until we hit the recCount
            int res = poll();
            if(res == 2) recCount+=2;
        }
        std::cout<<"One request fulfilled from thread "<< 
         std::this_thread::get_id() << std::endl;
        makeRequest(tradePartner,req2);
        while(recCount < 4){
            //make 2 requests, then poll until we hit the recCount
            int res = poll();
            if(res == 2) recCount+=2;
        }
        std::cout<<"Second request fulfilled from thread "<<
         std::this_thread::get_id() <<std::endl;
        //we've done the requests so we're done
    }

    void setPartner(Country* other){
        this->tradePartner = other;
    }
}Country;

#endif