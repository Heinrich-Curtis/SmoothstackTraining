/*
 *	Program that demonstrates the use of a couple lambda functions
 */
#include <iostream>

int main(){
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
return 0;
}
