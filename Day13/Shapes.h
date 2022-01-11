/*
 *	header file for all the mini-classes for this assignment
 */
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using std::cout;
using std::endl;

class Point{
	private:
		int m_x;
		int m_y;
	public:
		//default constructor
		/*
		Point(){
			std::cout<<"Point default constructor"<<std::endl;
			setX(0);
			setY(0);
		}
		*/
		//parameterized constructor
		Point(int x, int y) : m_x(x), m_y(y){
		//	cout<<"Point param constructor"<<endl;
		};
		//because this class has no dynamic memory, there is no need
		//to override the implicit copy/move constructors or operators

		//getters
		int x() const{
			return m_x;
		}
		int y() const{
			return m_y;
		}
		//setters
		void setX(int newX){
			m_x = newX;
		}
		void setY(int newY){
			m_y = newY;
		}
		//distance to anohter point
		float distance(const Point& p){
			float d;
			int xDist = x() - p.x();
			int yDist = y() - p.y();
			d = sqrt((xDist * xDist)+(yDist * yDist));
			return d;
		}
};

class Line {
	private:
		Point a;
		Point b;
	public: 
		Line(int aX, int aY, int bX, int bY) : a(aX,aY), b(bX, bY){
			//empty body b/c initializer list
		
			//moving the initiailizations pf the members into the 
			//initializer list instead of the body saves us 2 calls to
			//the point constructor and all allows us to leave Point's
			//default constructor undeclared (for now)	
		}

			
		//this class is still so simple that there is no need to 
		//override implicit constructors/operators
		//return the euclidean length of the line
		float length(){
			return a.distance(b);
		}
		//getters
		//in general, don't return references to class members, it breaks
		//encapsulation and doesn't actually save you anything. If 
		//the members start getting big in size and a return by 
		//reference may be a cost-saving measure, return const reference
		//instead
		Point getStart(){
			return a;
		}
		Point getEnd(){
			return b;
		}
		//setters
		void setStart(int x, int y){
			a.setX(x);
			a.setY(y);
		}
		void setEnd(int x, int y) {
			b.setX(x);
			b.setY(y);
		}
};

class MultiLine {
	private:
		std::vector<Line>* lines;
		float totalLength;
	public:
		//default constructor is an empty list
		MultiLine(){
			lines = new std::vector<Line>;
			Line l(0,0,0,0);
			lines->push_back(l);
			totalLength = 0;
		}
		//copy constructor
		MultiLine(const MultiLine& other){
			cout << "ML copy constructor" <<endl;
			//forgot to make a new thing here and it caused a double
			//free
			lines = new std::vector<Line>();
			lines->push_back(Line(0,0,0,0));
			for (Line l : *other.lines){
				Line line = l; //use Line's implict copy const.
				lines->push_back(line);
				totalLength += line.length(); 
			}
		}
		//copy assignment operator
		MultiLine& operator=(const MultiLine& other){
			cout << "ML copy assignment op" <<endl;
			if (this == &other) return *this;
			if (lines != nullptr){
				delete lines;
				lines = new std::vector<Line>();
				totalLength = 0;
			}
			for (Line l: *other.lines){
				Line line = l;
				lines->push_back(line);
				totalLength += line.length();
			}
			return *this;
		}
		//move constructor
		MultiLine(MultiLine&& other){
			cout << "ML Move constructor"<<endl;
			lines = other.lines;
			totalLength = other.totalLength;
			other.lines = nullptr;
			other.totalLength = 0;	
		}
		//move assignment operator
		MultiLine& operator=(MultiLine&& other){
			cout << "ML move assignment op" << endl;
			if (this == &other) return *this;
			if (lines != nullptr){
				delete lines;
			}
			//otherwise take their stuff
			lines = other.lines;
			totalLength = other.totalLength;
			other.lines = nullptr;
			other.totalLength = 0;
			return *this;
		}
		//destructor
		~MultiLine(){
			delete lines;
		}
		//get the total length of the multiline
		float length() const{
			return totalLength;
		}
		//return an lvalue reference to lines? No never do this
		std::vector<Line>*  getLines(){
			return lines;	
		}
		//returns the point at the tail end of the multiline, used to
		//find the start point of any new line to be added to the 
		//Multiline
		Point getEndPoint() const{
			return lines->back().getEnd();
		}
		//add a new point to the multiLine, return the new total Length
		//of the multiline
		float addPoint(const Point& p){
			Point s = getEndPoint();
			Line l(s.x(), s.y(), p.x(), p.y());
			lines->push_back(l);
			totalLength += l.length();
			return totalLength;
		}

		
};
//a shape 2D is a collection of at least 3 points that defines a closed
//circuit (a closed shape)
class Shape2D :{
	
};

class Ellipse : public Shape2D {

};

class Circle : public Ellipse {

};

class Polygon : public Shape2D {

};

class Triangle : public Polygon {

};

class Quadrilateral : public Polygon {

};

class Trapezoid : public Quadrilateral {

};

class Parallelogram : public Quadrilateral {

};

class Rhombus : public Parallelogram {

};

class Rectangle : public Parallelogram {

};

class Square : public Rhombus {

};


