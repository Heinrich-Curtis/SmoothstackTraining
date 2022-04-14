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
	return 0;
}
