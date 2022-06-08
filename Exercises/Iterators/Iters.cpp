/*
	playing around with iterators
*/
#include <vector>
#include <cassert>
#include <iostream>

int main(){
	std::vector<int> vec={2,3,4,6,8,2};
	//const auto way
	for (const auto& i : vec){
		std::cout << i << std::endl; 
	}
	//using at
	for (unsigned int i = 0; i < vec.size(); ++i){
		std::cout << vec.at(i) <<std::endl;
	}
	//explicitly make an iterator and use it
	for (auto it = vec.begin(); it != vec.end(); ++it){
		std::cout << *it << std::endl;
	}
	return 0;
}
