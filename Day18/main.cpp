/*
 * Class that mimics most of the function of the STL vector class. Implements
 * a vector backed by an array, which doubles in size when it gets filled.   
 */
 #include <iostream>
 #include <string>
 #include "myvec.h"
 #include <cassert>

//runs tests for vector and iterator
int main(){
    //build two vectors  of the same type
    MyVec<int> mvi1;
    MyVec<int> mvi2;
    assert(mvi1.capacity() == 8);
    //check if they're equal
    assert(mvi1 == mvi2);
    //add an element to one
    mvi1.push_back(1);
    //check if they're equal
    assert(mvi1 != mvi2);
    //add a different element to the other
    mvi2.push_back(2);
    //check if they're equal
    assert(mvi1 != mvi2);
    //pop stuff off
    mvi1.pop_back();
    assert(mvi1.size() == 0);
    try{
        mvi1.pop_back();
    }
    catch(std::out_of_range e){
        std::cout<<"Caught "<<e.what()<<" popping an empty vector"<<std::endl;
    }
    
    //make a third vector of a different type and add an element
    MyVec<double> mvd1;
    mvd1.push_back(2.5);
    //clear a vector
    mvd1.clear();
    assert(mvd1.size() == 0);
    //use the other constructor
    int ints[] = {1,4,5,6,7,8,9,9,0};
    MyVec<int> mvi3(ints,7);
    assert(mvi3.size() == 7);
    //check if we're out of ranging
    try{
    assert(mvi3[7] == 0);}
    catch(std::out_of_range e){
        std::cout<< " Caught an "<< e.what()<< "looking beyond size"<<std::endl;
    }
    assert(mvi3[6] == 9);
    assert(mvi3.at(0) == 1);
    //check the copy constructor
    MyVec<int> mvi4(mvi3);
    assert(mvi4.at(5) == mvi3.at(5));
    assert(mvi4.size() == mvi3.size());
    assert(mvi4.capacity() == mvi3.capacity());
    mvi4[3] = 0;
    assert(mvi4[3] != mvi3[3]);
    //check the assignment operators
    mvi1 = mvi3;
    assert(mvi1.size() == mvi3.size());
    assert(mvi1.capacity() == mvi3.capacity());
    mvi1.push_back(10);
    assert(mvi1 != mvi3);
    //move constructor
    MyVec<int> mvi5(std::move(mvi1));
    assert(mvi5.size() == (mvi3.size() + 1));
    assert(mvi1.size() == 0);
    assert(mvi1.capacity() == 0);
    //make sure we resize correctly
    mvi5.push_back(11);
    assert(mvi5.size() == 9);
    assert(mvi5.capacity() == 16);
    //check iterators
    MyVec<int>::Iterator it = mvi5.begin();
    assert(*it == 1);
    ++it;
    assert(*it == 4);
    --it;
    assert(*it == 1);
    //iterate through mvi5 in the stl-container-idiomatic way since we have begin() and end() defined
    for (int i : mvi5){
        std::cout<<i<<" ";
    }
    std::cout<<std::endl;

    return 0;
}