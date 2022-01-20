/*
 *	Program that demonstrates the use of a couple lambda functions
 */
#include <iostream>
#include <cmath>

//position vector
typedef struct R{	
	double xCoord;
	double yCoord;
}R;

// vector
typedef struct PhysVector{
	//direction, reuse R for this as the components of the vector
	R direction;
	//magnitude
	double magnitude;
}PhysVector;

//body struct
typedef struct body{
	int ind; //index of body
	double mass;
	R position;
	PhysVector velocity;
	PhysVector forceVector; //gonna need to keep the units straight since
	PhysVector acceleration;
}body;

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

int main(){
	
	//get the problem working with 2 bodies in one dimension first	
	//program parameters
	/* N bodies */
	const int N = 5; // this will be varied in loop (read below).
	/* Gravitational constant */
	const double G = 6.673e-11;
	//std::cout<<G<<std::endl;
	/* timestep */
	double timestep = 0.001;  // experiment with this!
	/* small mass */
	double initial_mass = 1.0; // experiment with this!
	/* num timesteps */
	double k = 100; // you can experiment with this! it can be fairly large.

	body bodies[N];
	for (int i = 0; i < N; i++){
		bodies[i].ind = i;
		bodies[i].mass = initial_mass;
		bodies[i].position = {(double)i,0}; // for this simple version, all the bodies
		//exist along a single line, the x -axis, I expect they all pull toward
		//each other and "orbit" the center in a single dimension
		bodies[i].velocity = {{0,0}, 0};
		bodies[i].acceleration = {{0,0},0};
		bodies[i].forceVector = {{0,0}, 0};
	}


	//other lambdas I'll need:
		//find an angle given an x and component
		auto getAngle = [](double hypo, double xPart){
			return acos(xPart/hypo);

		};
		//componentize a vector: given a force vector, return the x-component
		
		auto getForceXComponent = [](PhysVector force){
			//get the magnitude of the direction vector, the hypoteneuse
			//of the direction triangle
			double dirMag = sqrt(force.direction.xCoord * force.direction.xCoord + 
				force.direction.yCoord * force.direction.yCoord);
			return force.magnitude * force.direction.xCoord / dirMag; //is this right?
		};

		// given a force vector, return the y-component
	//Required lambdas:
	//update force on a body
		//find sum of forces on a body by iterating through the bodies and
		//computing F = -G(m1m2)/r^2
		//break each force into components and add to the body
	//update acceleration on a body
		//this is found by using F/m = a
	//update velocity of a body
		//this comes from cV + timestep*a
	//update position of a body
		//this is cP + timestep*v
	//compte distance between bodies in space
		//y = y2 -y1, x = x2 - x1, d = sqrt(y^2 + x^2)

	//disable this when we get the body stuff working
	//lambdaTests();

return 0;
}
