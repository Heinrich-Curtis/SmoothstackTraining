/*
 *	Program that demonstrates templating with an Account class that can
 *	have one of several currency types
 */
#include <iostream>
#include <string>
#include <cassert>
//conversion factors
#define DOLLARS_TO_YEN 113.91
#define DOLLARS_TO_POUND 0.73
#define DOLLARS_TO_EURO 0.88
#define EURO_TO_YEN 129.99
#define EURO_TO_POUND 0.83
#define POUND_TO_YEN 155.72

//simple money classes
class Dollars{
	public:
		double amount;
		//constuctors
		Dollars(): amount(0){}
		Dollars(double amt): amount(amt){}
};

class Euro{
	public:
		double amount;
		//constuctors
		Euro(): amount(0){}
		Euro(double amt): amount(amt){}
	
};

class Pound{
	public:
		double amount;
		//constuctors
		Pound(): amount(0){}
		Pound(double amt): amount(amt){}
	
};

class Yen{
	public:
		double amount;
		//constuctors
		Yen(): amount(0){}
		Yen(double amt): amount(amt){}
	
};

//convert class
class DollarsConverter{
	public:
		//to dollars
		Dollars operator()(Dollars d){
			return d.amount;
		}
		Dollars operator()(Euro e){
			return e.amount * (1/DOLLARS_TO_EURO); 
		}
		Dollars operator()(Pound p){
			return p.amount * (1/DOLLARS_TO_POUND);
		}
		Dollars operator()(Yen y){
			return y.amount * (1/DOLLARS_TO_YEN);
		}	
};

class EuroConverter{
	public:
		//to dollars
		Euro operator()(Dollars d){
			return d.amount * DOLLARS_TO_EURO;
		}
		Euro operator()(Euro e){
			return e.amount; 
		}
		Euro operator()(Pound p){
			return p.amount * (1/EURO_TO_POUND);
		}
		Euro operator()(Yen y){
			return y.amount * (1/EURO_TO_YEN);
		}	
};

class PoundConverter{
	public:
		//to dollars
		Pound operator()(Dollars d){
			return d.amount * DOLLARS_TO_POUND;
		}
		Pound operator()(Euro e){
			return e.amount * EURO_TO_POUND; 
		}
		Pound operator()(Pound p){
			return p.amount;
		}
		Pound operator()(Yen y){
			return y.amount * (1/POUND_TO_YEN);
		}	
};


//Account class
template <class T, class C>
class Account{
	private:
		T balance;
	public:
		//default and param constructors
		Account(): balance(0){}

		Account(T bal): balance(bal){}

		//copy constructor
		Account (const Account& a){
			balance = a.balance;
		}

		//move constructor
		Account (Account&& a){
			balance = a.balance;
			a.amount = 0;
		}

		//CAO
		Account& operator=(const Account& a){
			if (this == &a) return *this;
			balance = a.balance;
			return *this;
		}	

		//MAO
		Account& operator=(Account&& a){
			if (this == &a) return *this;
			balance = a.balance;
			a.balance = 0;
			return *this;
		}

		//comparison functions and operators
		template <typename X>
		bool is_same(T,X) const{
			return (typeid(T) == typeid(X));
		}

		template <typename X>
		bool operator==(const Account<X,C> a) const{
			C c;
			//if the types are the same
			if(is_same(balance, a.getBalance())){
				if (balance.amount == a.getBalance().amount){
					return true;
				}
				else {
					return false;
				}
			}
			//if the types aren't the same, we convert
			else{
				return (balance.amount == c(a.getBalance()).amount);
			}
		}
		
		//!= is just defined in terms of equal
		template <typename X>
		bool operator!=(const Account<X,C> a) const{
			return !(*this == a);
		}

		template <typename X>
		bool operator<(const Account<X,C> a) const{
			C c;
			//same currency
			if (is_same(balance, a.getBalance())){
				return balance.amount < a.getBalance().amount;
			}
			else{
				return balance.amount < c(a).getBalance().amounti;
			}
		}
		//I could define this in terms of < and ==, but I actually
		//think that's bad: 2 function calls for this one
		template <typename X>
		bool operator>(const Account<X,C> a) const{
			C c;
			if (is_same(balance, a.getBalance())){
				return balance.amount > a.getBalance().amount;
			}
			else{
				return balance.amount > c(a).getBalance().amount;
			}
		}

		template <typename X>
		T operator+(const X x){
			T t(balance.amount + x);
			return t;
		}

		template <typename X>
		T operator+=(const X x){
			T t(balance.amount + x);
			return t;
		}

		template <typename X>
		T operator-(const X x){
			T t(balance.amount - x);
			return t;
		}

		template <typename X>
		T operator-=(const X x){
			T t(balance.amount -= x);
			return t;
		}

		template <typename Q>
		T deposit(const Q q){
			C c;
			//same currency
			if (typeid(q) == typeid(balance)){
				balance.amount += q.amount;
			}
			else{
				balance.amount += c(q).amount;
			}
			return balance;
		}
		
		template <typename Q>
		T withdraw (const Q q){
			C c;
			if (typeid(q) == typeid(balance)){
				balance.amount -= q.amount;
			}
			else{
				balance.amount -= c(q).amount;
			}
			return balance;
		}

		T getBalance() const{
			return balance;
		}

		//cast operator
		template <typename Q>
		operator Account<Q, C>() const{
			C c;
			if (typeid(Q) == typeid(T)){
				Account<Q, C> account(balance.amount);
				return account;
			}
			else{
				Q q(c(balance));
				Account<Q, C> account(q);
				return account;
			}
		}

		template <typename R>
		Account<R, C>* currency(R r){
			if (typeid(R) == typeid(T)){
				R r(balance.amount);
				Account<R,C>* account = new Account<R, C>(r);
				return account;
			}
			else{
				C c;
				R r(c(r).amount);
				Account<R, C>* account = new Account<R, C>(r);
				return account;
			}
		}


};


int main(){
	Account <Dollars, DollarsConverter> account(100);
	Account <Euro, EuroConverter> account2(Euro(20));
	Account <Pound, PoundConverter> account3(Pound(25));
	assert(account.getBalance().amount == 100);
	assert(account2.getBalance().amount == 20);
	//deposit
	account.deposit(Dollars(25));
	assert(account.getBalance().amount == 125);
	account.deposit(Euro(8.80));
	assert(account.getBalance().amount == 135);
	account.deposit(Yen(1139.1));
	assert(account.getBalance().amount == 145);
	account.deposit(Pound(73));
	assert(account.getBalance().amount == 245);
	//withdraw
	account.withdraw(Dollars(25));
	assert(account.getBalance().amount == 220);
	account.withdraw(Euro(8.80));
	assert(account.getBalance().amount == 210);
	account.withdraw(Yen(1139.1));
	assert(account.getBalance().amount == 200);
	//operators
	Account<Euro, EuroConverter> account4(88);
	//this isn't quite what I want to be comparing here
	assert(account.getBalance().amount >  account4.getBalance().amount);
	return 0;
}
