/*
 *	Driver code that tests the classes and function in Shapes.h
 */
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "Shapes.h"
#include <cassert>

int main(){
	//make a bunch of the different types in Shapes.h
	//test them
//Point
	Point p(0,0);
	Point q(3,4);
	assert(p.distance(q) == 5.0);
	q = p;
	assert(p.distance(q) == 0.0);	
	Point r(-3,4);
	assert(r.distance(p) == 5.0);
	std::cout<<"Euclidean distance between points is correct"<<std::endl;
//Line	
	Line L1(0,0,3,-4);
	assert(L1.length() == 5.0);
	//get members
	Point l1s = L1.getStart();
	assert(l1s.x() == 0);
	assert(l1s.y() == 0);
//Multline, here's where it gets interesting
	Point s(3,4);
	Point t(6,0);
	MultiLine mL;
	mL.addPoint(s);
	assert(mL.length() == 5.0);
	mL.addPoint(t);
	assert(mL.length() == 10.0);
	std::cout<< "TotalLength of multi-line is correct"<<std::endl;
	//copy constructor
	MultiLine mLi(mL);
	Point u(-3,-4);
	Point v(-6,0);
	MultiLine mL2;
	mL2.addPoint(u);
	mL2.addPoint(v);
	//copy assignment operator
	assert(mL2.getLines()->back().getEnd().x() != 6);
	mL2 = mL;
	assert(mL2.getLines()->back().getEnd().x() == 6);
	//move constructor
	MultiLine mL3 = std::move(mL2);
	assert(mL2.getLines() == nullptr);
	assert(mL2.length() == 0);
	//move assignment operator
	mL3 = std::move(mLi);
	return 0;
}
