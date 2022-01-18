/*
 *	Program that demonstrates the use of a couple lambda functions
 */
#include <iostream>
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
	PhysVector* forceVector; //gonna need to keep the units straight since
	//they're all the same type
	PhysVector totalForce;
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
	
		
	//disable this when we get the body stuff working
	lambdaTests();

return 0;
}
