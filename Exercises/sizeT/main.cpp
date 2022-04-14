//check if we can get the size of a templated arg

#include <iostream>
#include <cassert>
#include <iostream>
#include <bitset>

template <typename T = int>
bool isPowTwo(int val){
	//constexpr int size = sizeof(T);
	//size *= 8; //get the number of bits
	return (std::bitset<32>(val).count()==1);
}

int main(){
	assert(isPowTwo<int>(2));
	assert(!isPowTwo<int>(3));
	assert(!isPowTwo<int>(0));
	assert(!isPowTwo<int>(-1));
	std::cout << "Tests passed" << std::endl;
	return 0;
}
