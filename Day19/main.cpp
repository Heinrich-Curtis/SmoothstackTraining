/*
 *	Program that demonstrates the use of a couple lambda functions
 */
#include <iostream>
#include <cmath>
#include <cassert>
#include <iomanip>

//forward declaration of a test function
void lambdaTests();
void bodyTests();

/* Gravitational constant */
const double G = 6.673e-11;
//double fudge factor;
const double EPSILON = 5e-5;
//position vector
typedef struct R{	
	double xCoord;
	double yCoord;
}R;

// vector
typedef struct PhysVector{
	//direction, reuse R for this as the components of the vector
	R components;// x component of vector and y component. x is positive right
		//and y is positive up
	double magnitude;
	//add two vectors componentwise
	PhysVector operator+(const PhysVector& other){
		PhysVector v;
		v.components.xCoord = this->components.xCoord + other.components.xCoord;
		v.components.yCoord = this->components.yCoord + other.components.yCoord;
		v.magnitude = sqrt(v.components.xCoord * v.components.xCoord +
			v.components.yCoord*v.components.yCoord);
		return v;
	}
}PhysVector;

//body struct
typedef struct body{
	int ind; //index of body
	double mass;
	R position;
	PhysVector velocity;
	PhysVector* forceVector; //pointer that stores all the components of the 
	//net force acting on this body, size is the number of bodies in the 
	//simulation
	int vSize; //keeps track of the number of elements in forceVector
	PhysVector netForce;
	PhysVector acceleration;
	body(){
		forceVector = nullptr;
		vSize = 0;
		mass = 0;
		ind = 0;
		position = {0,0};
		//everyone starts at rest
		netForce = {0,0,0};
		velocity = {0,0,0};
		acceleration = {0,0,0};
	}
	body(int n, int id, R pos, double m){
		forceVector = new PhysVector[n];
		vSize = n;
		mass = m;
		ind = id;
		position = pos;
		//everyone starts at rest
		netForce = {0,0,0};
		velocity = {0,0,0};
		acceleration = {0,0,0};
		
	}
	//need the copy constructor and CAO or we get double free
	body(const body& other){
		forceVector = new PhysVector[other.vSize];
		vSize = other.vSize;
		ind = other.ind;
		mass = other.mass;
		position = other.position;
		netForce = other.netForce;
		velocity = other.velocity;
		acceleration = other.acceleration;
	}

	body& operator=(const body& other){
		if (this == &other) return *this;
		if (forceVector != nullptr) delete[] forceVector;
		mass = other.mass;
		vSize = other.vSize;
		forceVector = new PhysVector[vSize];
		ind = other.ind;
		position = other.position;
		velocity = other.velocity;
		acceleration = other.acceleration;
		for (int i = 0; i < vSize; ++i){
			forceVector[i] = other.forceVector[i];
		}
		return *this;
	}
	//maybe need move constructor later

	~body(){
		if (forceVector != nullptr) delete[] forceVector;
	}
	
	//get gravitational force from another body
	//Gm1m2/r^2, the force always points from this to other
	PhysVector gForceFrom(const body& other){
		PhysVector v;
		//if we are other, skip all the math and return 0s
		if (this->ind == other.ind){ 
			v = {0,0,0};
			return v;
		}
		double y = other.position.yCoord - this->position.yCoord;
		double x = other.position.xCoord - this->position.xCoord;
		double distance = sqrt(x*x + y*y);
		//lambda that populates v
		[&](){
			//return result of math
			v.magnitude = G * this->mass * other.mass / (distance * distance);
		}();
		//get the vector components
		v.components.xCoord = v.magnitude * (x/distance);
		v.components.yCoord = v.magnitude * (y/distance);
		return v;
	}
	//uses the data stored int the forceVector array to calculate the net force
	PhysVector calcNetForce(){
		PhysVector netForce ={0,0};
		for (int i = 0; i < vSize; ++i){
			//add every element in forceVector to get netForce
			netForce = netForce + forceVector[i];
		}
		return netForce;
	}
	/*
	 * updates the acceleration, velocity and position of the body
	 * using lambdas. we tick after the net force on the body for the
	 * timestep has been calculated
	 */
	void tick(double& timestep){
		//the new acceleration is dependent on the net force on the body
		netForce = calcNetForce();
		//now with the net force, we can find the acceleration
		[&](){
			acceleration.magnitude = netForce.magnitude / mass;
			acceleration.components.xCoord = netForce.components.xCoord 
				/ mass;
			acceleration.components.yCoord = netForce.components.yCoord 
				/ mass;
		}();
		//with the instantaneous acceleration, we can find the new velocity
		[&](){
			velocity.components.xCoord = velocity.components.xCoord +
				acceleration.components.xCoord * timestep;
			velocity.components.yCoord = velocity.components.yCoord +
				acceleration.components.yCoord * timestep;
			velocity.magnitude = sqrt(velocity.components.xCoord * 
				velocity.components.xCoord + velocity.components.yCoord *
				velocity.components.yCoord);
		}();
		//with the velocity, we can find the new position
		[&](){
			position.xCoord = position.xCoord +
				velocity.components.xCoord * timestep;
			position.yCoord = position.yCoord +
				velocity.components.yCoord * timestep;
		}();
	}

	//print function prints a string with the characteristics to a stream
	//as a json object-y way
	void dump(std::ostream& stream){
		stream << "{ ";
		stream << "id : "<< ind << ", "<<std::endl;
		stream << "position : ["<<position.xCoord <<", " <<
			position.yCoord<<"], "<<std::endl;
		stream << "velocity : ["<<velocity.magnitude<<", "<<
			velocity.components.xCoord<<", "<<velocity.components.yCoord<<
			"], "<<std::endl;
		stream <<"acceleration : ["<<acceleration.magnitude<<", "<<
			acceleration.components.xCoord<<", "<<
			acceleration.components.yCoord<<"] "<< std::endl;
		stream << "}"<<std::endl;
	}
}body;

void dumpAll(body* bodies, int size, std::ostream& stream);

int main(){
	
	//get the problem working with 2 bodies in one dimension first	
	//program parameters
	/* N bodies */
	const int N = 2; // this will be varied in loop (read below).
	/* timestep */
	double timestep = 0.001;  // experiment with this!
	/* small mass */
	double initial_mass = 1.0; // experiment with this!
	/* num timesteps */
	double k = 250; // you can experiment with this! it can be fairly large.


	body bodies[N];
	int n = N;
	//setup the experiment
	for (int i = 0; i < n; i++){
		bodies[i] = body(n,i,{(double)i*0.0001,0},initial_mass);	
	}
	//for the tnumber of timesteps, get the netForce for one body and then
	//tick, dump to cout to check validity
	for (int i = 0; i < k; ++i){
		//only check the first one for now, no one else moves
		for (int j = 0; j < n; ++j){
			bodies[0].forceVector[j] = bodies[0].gForceFrom(bodies[j]);
		}
		bodies[0].dump(std::cout);
		bodies[0].tick(timestep);


	}


	//disable this when we get the body stuff working
	//lambdaTests();
	bodyTests();

return 0;
}

//dump all the bodies in the experiment
void dumpAll(body* bodies, int size, std::ostream& stream){
	for (int i = 0; i < size; ++i){
		bodies[i].dump(stream);
	}
}
//basic test of body and it's members
void bodyTests(){
	//simple default constrctor tests
	body b1;
	body b2;
	//straight line, same mass
	b1.ind = 0;
	b2.ind = 1;
	b1.position.xCoord = 0;
	b1.position.yCoord = 0;
	b2.position.xCoord = 1;
	b2.position.yCoord = 0;
	b1.mass = 1;
	b2.mass = 1;
	//b1.dump(std::cout);
	PhysVector v = b1.gForceFrom(b1);
	assert(v.magnitude == 0);
	v = b1.gForceFrom(b2);
	
	assert(v.magnitude == G);
	assert(v.components.xCoord == G);
	assert(v.components.yCoord == 0);
	b2.position.yCoord = 1;
	b2.position.xCoord = 0;
	//b2.dump(std::cout);
	v = b1.gForceFrom(b2);
	assert(v.magnitude == G);
	assert(v.components.xCoord == 0);
	assert(v.components.yCoord == G);
	b2.position.xCoord = 1;
	//now b2 is at 1,1
	v = b1.gForceFrom(b2);
	//check the vector components are really close to their ideal values
	//due to floating point fuckery
	assert(v.magnitude > G - EPSILON && v.magnitude < G + EPSILON);
	assert(v.components.xCoord > (sqrt(2)/2 * G) - EPSILON);
	assert(v.components.xCoord < (sqrt(2)/2 * G) + EPSILON);
	assert(v.components.yCoord > (sqrt(2)/2 * G) - EPSILON);
	assert(v.components.yCoord < (sqrt(2)/2 * G) + EPSILON);

	//now we test the more involved constructor and methods

}

//some basic usage of lambdas before trying to get the real stuff running
void lambdaTests(){
	int ints[] = {1,3,4,5,6,7,8,9,10};

	//operate on ints with a lambda that uses parameters
	for (int i = 0; i < 8; ++i){
	[](int a, int b){ 
		std::cout<< a << " + "<< b << " = "<< a + b<<std::endl;
		}(ints[i],ints[i+1]);
	}

	//now do it with a lambda that captures the data
	[&ints](){
		for (int i = 0; i < 8; ++i){
		//use a nested lambda
			std::cout<< ints[i] << " + "<< ints[i+1] << " = "<<
			       [](int a, int b){return a + b;}(ints[i],ints[i+1])<<std::endl;	
		}
	}();

}