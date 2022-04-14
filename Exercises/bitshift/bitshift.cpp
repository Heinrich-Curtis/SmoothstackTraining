//test bitshifting and bitset

#include <bitset>
#include <cassert>
#include <iostream>

int main(){
	int a = 4;
	assert((a << 1) == 8);
	std::cout << " Left shift is indeed <<" << std::endl;
	std::bitset<32> bs(a);
	assert(bs.count() == 1);
	std::cout << "It is indeed bs.count()" << std::endl;
	return 0;
}
