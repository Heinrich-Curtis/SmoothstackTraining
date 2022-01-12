/*
 *	Use the classes from yesterday and some new ones to demonstrate some
 *	properties of polymorphic classes
 */
#include <iostream>
#include <cassert>
#include <type_traits>
#include "Shapes.h"

//simple objects to demonstate is_copy_assignable property
struct F{};
struct G{
	int a;
	int b;
	G(int x, int y): a(x), b(y){
	
	}	
	G& operator=(const G& g) = delete;
};
class H{
	private:
		H& operator=(const H& h){ return *this;}
};


//test whether a couple things are copy assignable
bool copyAssignableTests(){
	std::cout<<"struct F is copy assignable because the implicit copy "
	       << "assignment operator is added to it" <<std::endl;
	assert(std::is_copy_assignable<struct F>::value);
	std::cout<<"int is copy assignable becausee all primitives are "
		<< "copy-assignable"<< std::endl;
	assert(std::is_copy_assignable<int>::value);
	std::cout<<"int[] is not copy-assignable because because arrays are "
		<<"const pointers,\nwhich means they're not move-assignable, "
		<<"\nwhich means they're not copy-assignable"<<std::endl;
	assert(!std::is_copy_assignable<int[2]>::value);
	std::cout<<"Struct G is not copy assignable because I explicitly "
		<<"deleted the copy assignment operator from it's definition"
		<<std::endl;
	assert(!(std::is_copy_assignable<struct G>::value));
	std::cout<< "Class H is not copy-assignable becasue I made its copy"
		<<" assignment operator private, which means it can't be "
		<<"\naccessed by function resolution for the operator"<<std::endl;
	return true;
}

bool PolymorphismTests(){
	//use a polymorphic pointer to show the appropriate behavior on some
	//objects
	Point p(0,0);
	Point q(2,3);
	int sideLen = 3;
	//make a rectangle and a square
	Rectangle r1(p,q);
	Square s1(p, sideLen);
	//pointer to a quadrilateral, a base class of both rectangle and square
	Quadrilateral* qP;
	//call the virtual methods setArea and setPerimeter on the objects and ensure
	//that those properties are set according to the appropriate method
	assert(r1.getArea() != 6.0);
	//set a rectangle's area
	qP = &r1;
	qP->setArea();
	assert(r1.getArea() == 6.0);
	//set a square's area
	qP = &s1;
	qP->setArea();
	assert(s1.getArea() == 9.0);
	std::cout<< "A pointer of type quadrilateral calls the appropriate"
		<<" methods when pointing to a rectangle versus a square, "
		<<"two classes that derive from quadrilateral"<<std::endl;
	return true;
}

int main(){

	copyAssignableTests();
	PolymorphismTests();

	return 0;
}
