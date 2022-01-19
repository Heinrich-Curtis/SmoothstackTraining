//test
#ifndef MYVEC_H
#define MYVEC_H
#include <typeinfo>
#include <stdexcept>

template<typename T>
class MyVec{
private:
    T* mData; // this is the actual data (or array)
	  int mSize; // Size is how much data.  Capacity is how much memory.
	  int mCapacity; // not always same as mSize, usually much larger than mSize.
	  T mUndefined;// Lots of STL functions say that doing something naughty gets "undefined behavior".
public:
    MyVec(){
        mData = new T[8];
        mSize = 0;
        mCapacity = 8;
    }
    MyVec(T* tPtr, int sz){
        //asking for a size less than 8 is stupid, so if anyone asks
        //for a size less than 8, we give them 8 anyway
        if (sz < 8){
            mCapacity = 8;
        }
        else {
            mCapacity = sz;
        }
        mData = new T[mCapacity];
        for (int i = 0; i < sz; ++i){
            mData[i] = tPtr[i];
        }
        mSize = sz;
    }
    virtual ~MyVec() {
        delete[] mData;
    }
    
	MyVec(const MyVec<T>& other) {
        mSize = other.mSize;
        mCapacity = other.mCapacity;
        mUndefined = other.mUndefined;
        mData = new T[mCapacity];
        for (int i =0; i < mSize; ++i){
        mData[i] = other.mData[i];
        }
    }
	MyVec(MyVec<T>&& other) {
        mSize = other.mSize;
        mCapacity = other.mCapacity;
        mUndefined = other.mUndefined;
        mData = other.mData;
        other.mData = nullptr;
        other.mSize = 0;
        other.mCapacity = 0;
    }
	MyVec& operator=(const MyVec<T>& other) {
        if (this == &other){
            return *this;
        }
        if (mData != nullptr){
        delete[]  mData;
        } 
        mCapacity = other.mCapacity;
        mSize = other.mSize;
        mUndefined = other.mUndefined;
        mData = new T[mCapacity];
        for (int i = 0; i < mSize; ++i){
            mData[i] = other.mData[i];
        }
        return *this;
    }
    //two vectors are equal if they have the same current size
    //and all the elements are equal, capacity doesn't matter
	bool operator==(const MyVec<T>& other) {
        //check the easy things first
        // I'm making the convention that two empty vectors are equal
        //no matter what types they hole
        if ((mSize == 0) && (other.mSize == 0)) return true;
        if (mSize != other.mSize) return false;
        //we don't need to consider this because the definition
        //implies both types have the same 'T', the compiler will
        //complain you haven't defined a method that compares
        //templates with different instantiated types.
        //We could do this by declaring a second template type
        //U and then comparing typeid T to typeid U, but why bother?
        //if (typeid(mData[0]) != typeid(other.mData[0])) return false;
        for (int i = 0; i < mSize; ++i){
            if (mData[i] != other.mData[i]) return false;
        }
        return true;
    }
    bool operator!=(const MyVec<T>& other){
        return !((*this)==other);
    }
    T& operator[](int offset) {
        if (offset > (mSize - 1)){
            //throw an execption
            throw(std::out_of_range("out of range"));
        }
        return mData[offset];
    }
    void push_back(const T& t) {
        if (mSize)
        if (mSize == mCapacity){
            reserve(mCapacity);
        }
        mData[mSize++] = t;
    }
    void pop_back() {
        if (mSize == 0) throw(std::out_of_range("out of range"));
        //just adjust the size down, leave the data there? Push_back
        //will overwrite, other methods operate on mSize
        --mSize;
    }
    T& at(int offset) {
        if (offset > (mSize - 1))throw(std::out_of_range("out of range"));
        return mData[offset];
    }
    void clear() {
        mSize = 0;
        mCapacity = 8;
        delete[] mData;
        mData = new T[mCapacity];
    }
    int size() const {return mSize;}
    void reserve(int tCount) {
        T* newData = new T[mCapacity +  tCount];
        //handle bad alloc someday
        for (int i = 0; i < mSize; ++i){
            newData[i] = mData[i];
        }    
        delete[] mData;
        mData = newData;
        mCapacity = mCapacity + tCount;
    }
    int capacity() const{return mCapacity;}
// iterator
    class Iterator {
        friend MyVec;
        const MyVec* myvec;
        int current; // offset 
    public:
        Iterator(const MyVec* vec, int offset): myvec(vec), current(offset) {
            //blank, initializer list
    }
        void operator++(){
        current++;
    }
        void operator--(){
        current--;
    }
        bool operator==(const Iterator& other){
        //two iterators are equal if their internal pointers
        //are equal
        return &(myvec->mData[current]) == 
        &(other.myvec->mData[other.current]);
    }
        bool operator!=(const Iterator& other){
        return !(*this == other);
    }
        //don't I need to make this a prefix operator, test this
        //does no argument make it unary as opposed to the binary?
        T& operator*(){
        return myvec->mData[current];
    }
    
    };
    Iterator begin() const {
        Iterator it(this, 0);
        return it;
    }
    Iterator end() const{return Iterator(this, mSize);};
};
#endif
