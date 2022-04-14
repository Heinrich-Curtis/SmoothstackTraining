//file that shows some neat things with pointers
#include <type_traits>
#include <cassert>
#include <iostream>
#include <new> //for set_new_handler
#include <string>
struct B{};

std::string res;
//callback function for failed to get memory error
void OoM_handler(){ //has to have signature int (size_t)
    res = "OoM";
}

int main(){
    int* pi = nullptr;
    int i = 0;
    pi = &i;
    if /*constexpr*/ (pi){ //can't constexpr here because constexpr is a compile-time constant, and the value of pi is not definitely known at compile time
    
    }
    //C++17 feature
    assert(std::is_pointer_v<int*>);
    assert(!std::is_pointer_v<B>);
    /*
        note that certain templates CAN be used in constexprs becasue templates are instantiated at compile-time, so the types are known to the
        compiler and the value of the statement above can be verified at compile time
    */

    std::set_new_handler(OoM_handler);
    unsigned long long l = 120000000000;
    int* p = new int [l];
    //why isn't this working?
    assert(p);
    assert(res == "OoM");   
    std::cout<<"Everything is good"<<std::endl;

    return 0;
}