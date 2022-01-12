/*
 * Program that makes use of a function that multiplies two floats iff both
 * are representable as an integer. Otherwise it throws an exception	
 */
#include <iostream>
#include <cassert>
#include <exception>

//define function as noexcept so std::terminate is called if we ever throw
bool compareFloats(float a, float b) noexcept{
	//to check if a float can be represented by an int, we just cast it to
	//int and then back to float, and see if the values are the same
	int ai =(int)a;
	float af = (float)ai;
	if (af != a) throw(std::exception());
	int bi = (int) b;
	float bf = (float)bi;
	if (bf != b) throw(std::exception());
	//if we haven't thrown by now, we're good
	return a < b;
}

int main(){
	float a = -1;
	float floats[] = {1.0, 3.0, -4, 1024.0};
	//run the function with a couple valid values
	for (int i = 0; i < 4; ++i){
		compareFloats(a,floats[i]);	
		std::cout<< a <<" and "<< floats[i] << " are representable"
			<<" as ints" <<std::endl;	
	}	
	//try to run the function on a value that has any fractional part
	//and std::terminate gets called
	
	//it works if either argument has a fractional part, but terminate
	//obviously can only be called once
	std::cout<< "but 1.5 is not" <<std::endl;
	compareFloats(2.0, 1.5);
	//compareFloats(1.5, 2.0);
	return 0;

}
