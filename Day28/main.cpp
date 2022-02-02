#include <iostream>
#include <coroutine> //shows me a compiler error but compiles anyway
#include <random> //for uuids
#include <chrono> //timer stuff
#include <string> 

//enum for transaction types
enum transTypes {credit, debit};

//helper for printing enum
std::string printEnum(const transTypes& e){
	std::string res;
	if (e) return res = "debit";
	else return res = "credit";
}

//generate the uuids for account IDs
std::string get_uuid() {
	//infrastructure for randomness
    static std::random_device dev;
    static std::mt19937 rng(dev());
    std::uniform_int_distribution<int> dist(0, 15);

	//available options to pick from and spots to put them into 
    const char *v = "0123456789abcdef";
    // a 1 means there's a dash in the spot, otherwise a number can go there
	const bool dash[] = { 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0 };
	
	//return a string
    std::string res;
    for (int i = 0; i < 16; i++) {
        if (dash[i]) res += "-";
        res += v[dist(rng)];
        res += v[dist(rng)];
    }
    return res;
}

struct transaction{
   std::string post_date; // post date of transaction
   std::string src_accountId;  // use UUIDs
   std::string dest_accountId;  // use UUIDs
   transTypes tranType; // transaction type enum can be credit or debit
   double amount; // in dollars ranging [1..1000000]

   transaction(){
	    //all required fields from assignment
        post_date = getDate();
        src_accountId = get_uuid();
        dest_accountId = get_uuid();
		//just randomly assign transaction types
        tranType = std::rand() % 2 ? transTypes::credit : transTypes::debit;
		//just some arbitrary amount in cents
        amount = rand() % 20000;
    }

	//get the date that the transaction was created and return a nice string
	std::string getDate(){
		std::string dateString, monString, yearString;
		time_t rawTime;
		struct tm* timeinfo;
		time(&rawTime);
		timeinfo = localtime(&rawTime);
		dateString = asctime(timeinfo);
		monString = dateString.substr(4,6);
		yearString = dateString.substr(19,5);
		dateString = monString + yearString;
		return dateString;
	}

	//print the transaction
    void printTrans(){
        std::cout << "Post date: " << post_date << std::endl;
        std:: cout << "From account: " << src_accountId << std::endl;
        std:: cout << "To account: " << dest_accountId << std::endl;
        std:: cout << "Transaction type: " << printEnum(tranType) << std::endl;  
		//display amount in dollars      
        std::cout << "For amount: " << amount / 100 << std::endl;
		std::cout << std::endl;
    }
};
//this stuct encapsulates the coroutines to assist in their creation and destruction
template<typename T>
struct Generator {
    struct promise_type;
    using handle_type = std::coroutine_handle<promise_type>;
    
    Generator(handle_type h): coro(h) {
    }
    //generator needs this type
	handle_type coro;
    //destructor
    ~Generator() {
        if ( coro ) coro.destroy();
    }

    Generator(const Generator&) = delete;
    
    Generator& operator = (const Generator&) = delete;
    
    Generator(Generator&& oth): coro(oth.coro) {
        oth.coro = nullptr;
    }
    
    Generator& operator = (Generator&& oth) {
        coro = oth.coro;
        oth.coro = nullptr;
        return *this;
    }
    
    transaction getNextValue() {
        coro.resume();
        return coro.promise().current_value;
    }
    //boilerplate type stuff needed for coroutines
    struct promise_type {
        promise_type() {
        }                              
        
        ~promise_type() {
        }
		//details about when to suspend
        std::suspend_always initial_suspend() {  
            return {};
        }

        std::suspend_always final_suspend() noexcept {
            return {};
        }
        //get/return
        auto get_return_object() {      
            return Generator{handle_type::from_promise(*this)};
        }
		//yielding an object
        std::suspend_always yield_value(transaction value) {    
            current_value = value;
            return {};
        }
        
        void return_void() {}
        //in the case of exceptions we just exit
        void unhandled_exception() {
            std::exit(1);
        }
        
        T current_value;
    };
};

//the function that actually does the generation
Generator<transaction> getNext() {
    auto value = transaction();
    while (true) {
        co_yield value;
        value = transaction();
    }
}
//just call the generator a bunch
int main(void){
    auto gen = getNext();
    for (int i = 0; i <= 10; ++i) {
        auto val = gen.getNextValue();
        val.printTrans();
    }
}