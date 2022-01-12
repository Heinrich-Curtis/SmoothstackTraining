/*
 *	header file for all the mini-classes for this assignment
 */
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using std::cout;
using std::endl;

#define PI 3.1415
class Point{
	private:
		int m_x;
		int m_y;
	public:
		//default constructor
		
		Point(){
			std::cout<<"Point default constructor"<<std::endl;
			setX(0);
			setY(0);
		}
		
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
//a shape 2D is an abstract class that defines some closed shape that has a
//perimeter and an area
class Shape2D {
	protected:
		float area;
	public:
		//getters
		virtual float getArea() const{ return area;}
		virtual void setArea() = 0;
};
// an ellipse is a curved 2d shape defined by a major and minor axis
// I forget how to calculate the area and perimeter of the ellipse,
// so I'll just add the property for circumference and let Circle 
// do the easier version
class Ellipse : public Shape2D {
	protected:
		float circumference;
	public:
		//parameterized constructor
		Ellipse(float circ): circumference(circ){
			//empty
		}
		//the implicit constructors and assignment operators will be fine here
		float getCircumference(){
			return circumference;
		}
		void setCircumference(float circ){
			circumference = circ;
		}
		//don't define getP or getA here
};
//A circle is an ellipse with a much easier to calculate area
class Circle : public Ellipse {
	protected:
		float radius;
		//this is private b/c public interface only allows changing
	private:		//the radius
		virtual void setArea(){
			area = 	radius * radius * PI;
		}

	public:
		//default constructor
		Circle(): Ellipse(0){
			radius = 0;
			setCircumference(0);
			setArea();
		}
		//param constructor
		Circle(float rad): Ellipse(0), radius(rad){
			setCircumference(rad * 2 * PI);
			setArea();
		}	
		
		//default constructors and assignment operators are fine here
		//override of virtual method
		virtual float getArea() const{
			return area;
		}

		float perimeter(){
			return radius * 2 * PI ;	
		}
		float circumference(){
			return perimeter();
		}
		void setRadius(float rad){
			radius = rad;
			setArea();	
		}


};
// a polygon is a shape2d that has an array of points that define the edges of
// the shape
class Polygon : public Shape2D {
	protected:
		//these define the shape: the path around a polygon goes from
		//the first vertex, to the second, the third....the last "leg"
		//of the polygon goes from the final vertex back to the first
		//one
		Point* vertices;
		//the sum of the distances between the vertices
		float perimeter;
	public:
		float getPerimeter() const{return perimeter;}
		void setPerimeter(float p){perimeter = p;}
		//do we need a virtual destructor here? look for memory issues
		virtual  ~Polygon(){
			delete[] vertices;
		}
};
//polygon with 3 sides
class Triangle : public Polygon {
	public:
	//default constructor
	Triangle(){
		std::cout <<"Tri DC"<<std::endl;
		vertices = new Point[3];
		setPerimeter(0);
		setArea();
	}
	//param consturctor takes 3 points and uses them to set all the members
	Triangle(Point a, Point b, Point c){
		std::cout<< "Tri PC" << std::endl;
		//uses point's copy consturctor
		vertices = new Point[3];
		vertices[0] = a;
	       	vertices[1] = b;
		vertices[2] = c;
		setPerimeter(a.distance(b) + b.distance(c) + c.distance(a));
		setArea();
	}
	//copy constructor
	Triangle(const Triangle& tri){
		std::cout << "Tri CC" <<std::endl;
		vertices = new Point[3];
		for (int i = 0; i < 3; ++i){
			vertices[i] = tri.vertices[i];
		}
		perimeter = tri.getPerimeter();
		area = tri.getArea();
	}	
	//copy assingment operator
	Triangle& operator=(const Triangle& tri){
		std::cout <<"Tri AssOp" <<std::endl;
		if (this == &tri) return *this;
		if (vertices != nullptr){
			delete[] vertices;
		}
		vertices = new Point[3];
		for (int i =0; i < 3; ++i){
			vertices[i] = tri.vertices[i];
			perimeter = tri.getPerimeter();
			area = tri.getArea();
		}
		return *this;

	}
	//move constructor
	Triangle(Triangle&& tri){
		std::cout<< "Tri MC" <<std::endl;
		vertices = tri.vertices;
		perimeter = tri.getPerimeter();
		area = tri.getArea();
		tri.vertices = nullptr;
		tri.perimeter = 0;
		tri.area =  0;
	}
	//move assignment operator
	Triangle& operator=(Triangle&& tri){
		std::cout <<"Tri MO"<<std::endl;
		if (this == &tri) return *this;
		vertices = tri.vertices;
		perimeter = tri.getPerimeter();
		area = tri.getArea();
		tri.vertices = nullptr;
		tri.perimeter = 0;
		tri.area = 0;
		return *this;
	}
	//destructor is handled by Polygon's virtual destructor, I don't need
	//to write these
	/*
	~Triangle(){
		delete[] vertices;
	}
	*/
	//overload of virtual function: the math here isn't right for all
	//triangles, but it's right for right triangles, which is all I'll 
	//pass it in this program
	void setArea(){
		area = 0.5 * (vertices[1].x() - vertices[0].x()) *
			(vertices[2].y() - vertices[0].y());
	}
};
//a polygon with 4 sides
class Quadrilateral : public Polygon {
	//default constructor
	public:
	Quadrilateral(){
		vertices = new Point[4];
		area = 0;
		perimeter = 0;
	}
	//param constructor
	Quadrilateral(const Point* points){
		vertices = new Point[4];
		for (int i =0; i < 4; ++i){
			vertices[i] = points[i];
		}
		setPerimeter();
	}
	//CC
	Quadrilateral(const Quadrilateral& q){
		vertices = new Point[4];
		for (int i = 0; i < 4; ++i){
			vertices[i] = q.vertices[i];
		}
		perimeter = q.perimeter;
		area = q.area;
	}
	//MC
	Quadrilateral(Quadrilateral&& q){
		vertices = q.vertices;
		perimeter = q.perimeter;
		area = q.area;
		q.vertices = nullptr;
		q.perimeter = 0;
		q.area = 0;
		
	}
	//CAO
	Quadrilateral& operator=(const Quadrilateral& q){
		if (this == &q) return *this;
		if (vertices != nullptr){
			delete[] vertices;
			vertices = new Point[4];
		}
		for (int i =0; i < 4; ++i){
			vertices[i] = q.vertices[i];
		}
		area = q.area;
		perimeter = q.perimeter;
		return *this;
	}	
	//MAO
	Quadrilateral& operator=(Quadrilateral&& q){
		if (this == &q) return *this;
		if (vertices != nullptr){
			delete[] vertices;
		}
		vertices = q.vertices;
		perimeter = q.perimeter;
		area = q.area;
		q.vertices = nullptr;
		q.perimeter = q.area = 0;
		return *this;
	}
	//destructor handled by polygon's virtual destructor
	//void setArea(){}
	//perimeter. I'm not gonna do area for this one
	void setPerimeter(){
		float p = 0.0;
		p += vertices[3].distance(vertices[0]);
		p += vertices[1].distance(vertices[0]);
		p += vertices[2].distance(vertices[1]);
		p += vertices[3].distance(vertices[2]);
	}
};
// a rectangle is a quadrilateral where all inner angles are
// 90. This means there are always 2 sets of same-length sides
class Rectangle : public Quadrilateral {
	//because of the angles involved, a rectangle can be 
	//defined by exactly 2 points, either of the 2 opposing 
	//corners give us the height and width of the rectangle
	public:
		//default constructor
		Rectangle(){
			//only 2 points are needed to define a rectangle: and
			//I establish the convention that point 0 is the top
			//left corner and point 1 is the bottom right corner
			//we don't need to allocate for vertices here because
			//the constructor for quadrilateral already did it
			//vertices = new Point[2];
			perimeter = 0;
			area = 0;
		}
		//PC
		Rectangle(const Point& topLeft, const Point& bottomRight){
			//vertices = new Point[2];
			vertices[0] = topLeft;
			vertices[1] = bottomRight;

		}
		//CC
		Rectangle(const Rectangle& r){
			//vertices = new Point[2];
			vertices[0] = r.vertices[0];
			vertices[1] = r.vertices[1];
			perimeter = r.perimeter;
			area = r.area;
		}
		//MC
		Rectangle (Rectangle&& r){
			vertices = r.vertices;
			perimeter = r.perimeter;
			area = r.area;
			r.vertices = nullptr;
			r.perimeter = 0;
			r.area = 0;
		}
		//CAO
		Rectangle& operator=(const Rectangle& r){
			if (this == &r) return *this;
			if (vertices !=nullptr){
				delete[] vertices;
				vertices = new Point[2];
			}
			vertices[0] = r.vertices[0];
			vertices[1] = r.vertices[1];
			perimeter = r.perimeter;
			area = r.area;
			return *this;
		}
		//MAO
		Rectangle& operator=(Rectangle&& r){
			if (this == &r) return *this;
			vertices = r.vertices;
			perimeter = r.perimeter;
			area = r.area;
			r.vertices = nullptr;
			r.area = 0;
			r.perimeter = 0;
			return *this;
		}
		//destructor handled by polygon
		/*		
		~Rectangle(){
			delete[] vertices;
		}
		*/
		
		//setters
		void setArea(){
			area = (vertices[1].x() - vertices[0].x()) *
				(vertices[0].y() - vertices[1].y());
		}
		void setPerimeter(){
			perimeter = 2 * ((vertices[1].x() - vertices[0].x())
					+(vertices[0].y() - vertices[1].y()));
		}
};

class Square : public Rectangle {
	//a square is a rectangle that has 4 sides of the same length, so we
	//only need any two points for a square
	//
	//make it convention that we're still looking at the topleft and bottom
	//right corners and we're always parallel to the axes
	//constructors
	//leave the destructor blank and check for leaks
	public:
	//default constructor just calls rectangles
	Square(){
	
	}

	//param constructor takes a single point representing the top left
	//and an int representing the side length, and uses this to place
	//the second vertex
	Square(const Point& p, int sideLen){
		vertices[0] = p;
		vertices[1].setX(p.x() + sideLen);
		vertices[1].setY(p.y() + sideLen);
		//don't call set area or perim so we can do in virtual call
	}
	// setArea and perimeter aren't called in the constructor so we
	// can call them via virtual pointer
	void setArea(){
		area = (vertices[1].x() - vertices[0].x()) * (vertices[1].y()
				-vertices[0].y());
	}

	void setPerimeter(){
		return Rectangle::setPerimeter();
	}
	//destructor handled by polygon?
	/*
	~Square(){
		delete[] vertices;
	}
	*/
};


