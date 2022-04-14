//do some little template stuff
#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <numeric>
#include <cassert>

template<typename T> 
T add(T a, T b){
	return a + b;
}
template<typename T, typename ContIT>
T sum(T& type, ContIT a, ContIT b){
	T total = std::accumulate(a,b,0);
	return total;
}

int main(){
	int iA = 4, iB = 3;
	double dA = 2.7, dB = 1.1;
	std::string  sA = "Hello ", sB = "World";
	std::cout << "ints:" << add(iA,iB) <<std::endl;
	std::cout << "doubles:" << add(dA,dB) << std::endl;
	std::cout << "strings:" << add(sA,sB) << std::endl;
	std::vector<int> vals = {1,3,4,5,6};
	int j;
	sum(j,vals.begin(), vals.end());
	return 0;
}
