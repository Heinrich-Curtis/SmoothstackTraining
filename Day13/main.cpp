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
//Circle/Ellipse
	Circle c;
	assert(c.getArea() == 0);
	Circle c1(1.0);
	assert(c1.getArea() < 3.16);
	c1.setRadius(2.0);
	assert(c1.getArea() > 6.0);
	std::cout << "Getting/Setting Circle looks okay" <<std::endl;
	//constructors/operators
	Circle c2(c1);
	assert(c1.getArea() == c2.getArea());
	Circle c3(10.0);
	c2 = c3;
	assert(c2.getArea() != c1.getArea());
	std::cout<< "Circle copies are okay" <<std::endl;
	Circle c4(std::move(c));
	c4 = std::move(c3);
	std::cout << "Circle moves okay" <<std::endl;
//Triagnge/Polygon
	q = Point(3,4);
	Point points[3] = {p,t,q};
	Triangle tri2(points[0],points[1],points[2]);
	Triangle tri1;
	assert(tri1.getArea() == 0.0);
	assert(tri2.getArea() == 12.0);
	//constructors/operators
	Triangle tri3(std::move(tri2));
	assert(tri3.getArea() == 12.0);
	assert(tri2.getArea() == 0);
	tri2 = std::move(tri3);
	tri3 = tri2;
	Triangle tri4(tri3);
//Rectangle and square
	Rectangle r1;
	Square s1;
	Square s2;
	Point x(0,3);
	Point y (2,0);
	//build a rectangle from x and y, and a square from x and a size
	Rectangle r2(x,y);
	r2.setArea();
	assert(r2.getArea() == 6.0);
	s2 = Square(x,3);
	s2.setArea();
	assert(s2.getArea() == 9.0); 	
	
	return 0;
}
