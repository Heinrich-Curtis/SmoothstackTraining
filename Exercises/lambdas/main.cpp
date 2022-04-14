//use some lambdas
#include <iostream>
#include <algorithm>
#include <vector>
//#include <execution> //for execution policy
#include <cassert>

int main(){
    //populate a vector
    std::vector<int> v;
    for (int i = 9; i >= 0; --i){
        v.push_back(i);
    }
    //now sort it using a lambda comparator: [&] is "capture everything by reference", [=] is "capture everything by value"
    //[=a,&b] capture a by value, b by reference
    //[&, =b] capture everything by reference except b
    //[&, &b] doing anything like this is an error, only one value and one refence designator can appear
    //[this] capture this by reference
    //[*this] capture this by value c++17                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
    int sum = 0;
    //in the lambda, we can just pass in the value that the iterator is pointing to in the args. We capture sum by refrerence so we can change it
    std::for_each(/*std::execution::seq,*/v.begin(),v.end(),[&sum](int i){sum +=i;});
    assert(sum == 45);
    //lambdas not inside functions or whatever are a statement and need a ;
    auto add = [](int x, int y){ return x + y;};
    // we have to call on add to get the return value type for auto, we can't just use add(3,5) as an expression in the assert
    int x = add(3,5);
    assert(x == 8);
    /*
    float z = 3.0;
    float s = 5.0;
    assert(y == -2.0f);
    */
    std::cout<<"Everything is fine"<<std::endl;

}