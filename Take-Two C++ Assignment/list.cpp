//write a method that takes an input list of integers, and returns the list with all the duplicates removed
#include <list>
#include <iostream>
#include <functional>

//take an input list and return a list with no dupes
std::list<int> removeDupes(const std::list<int>& inputList){
    std::list<int> res;
    for (int i : inputList){
	int j = i;
        std::list<int>::iterator it;
        it = std::find(res.begin(),res.end(),i);
        if (it == res.end()){
            res.push_front(j);
        }
    }
    return res;
}
int main(){
    std::list<int> list{1,1,1,6,2,3,3,4,5,8,8};
    std::list<int> res = removeDupes(list);
    for (int n : res){
        std::cout << n << " ";
    }
    std::cout << std::endl;
}
