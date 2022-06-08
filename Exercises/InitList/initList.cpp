//play with initializer list
#include <iostream>
#include <cassert>

class Class{
	public:
	int a, b, c, d;
	//default constructor
	Class(){
		a = 0;
		b = 0;
		c = 0;
		d = 0;
	}
	//overloaded constructor with init-list
	Class(int e, int f, int g, int h): a(e), b(f), c(g), d(h){
		//body now empty, initializer list did it
	}
	virtual void print(){
		std::cout << "Base print" << std::endl;
	}
	virtual ~Class(){}//doesn't actually do anything
};

//let's mess with some virtual stuff
class Derived : public Class{
	public:
	float e, f;

	Derived():e(0.0),f(0.0){}
	Derived(float ne, float nf):e(ne),f(nf){};
	virtual void print(){
		std::cout<< "Derived Print" << std::endl;
	}
};

class Bottom : public Derived{
//using Class::print; adding this using makes the virtual chain end at base because there's no where lower to go
	//add a member no one else has
	int* arr;
	public:
	Bottom(){
		arr = new int[5];
	}
	//what happens if no one calls this by using the base thing?
	~Bottom(){
		if (arr != nullptr){
		delete[] arr;
		}
	}
	void print(){
		std::cout <<"Bottom print"<< std::endl;
	}
};


int main(){
	Class c1;
	assert(c1.a == 0);
	assert(c1.b == 0);
	assert(c1.c == 0);
	assert(c1.d == 0);
	Class c2(1,2,3,4);
	assert(c2.a == 1);
	assert(c2.b == 2);
	assert(c2.c == 3);
	assert(c2.d == 4);
	//mess around with the inheritance
	Class base;
	Class* bp = &base;
	bp->print(); //should call base print
	Derived der;
	bp = &der;
	bp->print(); //should call derived print?
	Bottom bot;
	bp = &bot;
	bp->print(); //should call bot print?
	Derived* dp = &bot; //bot print?
	dp->print();
	Class* b = new Bottom();
	delete b;// here is where the resource leak happens
	// do we get all the memory back, or leak?
	return 0;
}
