//this program demonstrates some properties of function overloading
#include <iostream>
#include <cassert>
#include <vector>

//an add function
int add(int a, int b){
    return a + b;
}

//this is fine, number of arguments is different
int add(int a, int b, int c){
    return a + b + c;
}

//this is fine, the type of the arguments is different
float add(int a, float b){
    return a + b;
}

//I'm surprised I can do this, but I guess it's the template argument, so the signature isn't exactly the same as either of the above
template<typename T>
T add(T a, T b){
    return a + b;
}

/*
this is not allowed: functions cannot be overloaded on the basis of return type alone, redefinition of add
bool add(int a, int b){
    return (a + b) > 5;
}
*/

/*
  This is not allowed, because default arguments are not part of the function type

int add(int a = 5, int b = 3){
    return a + b;
}
*/
std::string res;

//overloading a function by changing a concrete type to a const reference with also produce unexpected results

void sum(int arr[]){
    res = "int";
}

//this is fine even if the types are probably the same as long as the types are different: long is basically an alias for int
void sum(long arr[]){
    res = "long";
}

void sum(short arr[]){
    res = "short";
}

//this is fine because of the constness of the argument
void sum(const int arr[]){
    res = "const int";
}

void sum(unsigned int arr[]){
    res = "unsigned int";
}

struct C{
    std::vector<int> data;
    //if the object is an lvalue, we do this
    void getData() & {
        res = "lvalue";
    }
    //if the thing being pointed to is an r-value about to be destroyed, we do this
    void getData() && {
        res = "rvalue";
        std::move(data);
    }
};

// call them all and assert some behavior
int main(){
    int ir = 0;
    float fr = 0;

    ir = add(3,4);
    assert(ir == 7);

    fr = add(3, 4.0f);
    //the int should get promoted to float
    assert(fr == 7.0f);

    ir = add<int>(7,11);
    assert(ir == 18);

    fr = add<float>(7.0f, 10.0f);
    assert(fr == 17.0f);

    int myarr[] = {2,3,4};
    sum(myarr);
    assert(res == "int");

    const int carr[] = {3,4,5};
    sum(carr);
    assert(res == "const int");

    C c;
    c.getData();
    assert(res == "lvalue");
    C().getData();
    assert(res == "rvalue");

    std::cout<<"Everything works"<<std::endl;
    return 0;
}
