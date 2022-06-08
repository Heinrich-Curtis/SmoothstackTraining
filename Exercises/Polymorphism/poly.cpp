/*
    Play around with object polymorphism a bit
*/
#include <iostream>

class A
{
    public:
    void print()
    {
        std::cout << "A" << std::endl;
    }
};

class B: public A
{
    public:
    virtual void print()
    {
        std::cout << "B" << std::endl;
    }
};

class C: public B
{
    public:
    int* pi;
    C()
    {
        pi = new int(5);
    }
    ~C()
    {
        delete pi;
    }
    void print()
    {
        std::cout << "C" << std::endl;
    }
};

class D: public C
{
    public:

    void print()
    {
        std::cout << "D" << std::endl;
    }
};

class E : public C //final on this line means "no class may derive from E"
{
    public:
    virtual void print() //final //final here means "no derived class may override print"
    {
        std::cout << "E" << std::endl;
    }
};

class F : public E
{
    public:
    virtual void print()//final here means "no derived class may override print"
    {
        std::cout << "F" << std::endl;
    }
};
/*
class F: public D, public E //have to virtualize a base to solve diamond problem. Virtualzing the bases doesn't stop the ambiguous function call error though, just including the members of the grandparent twice
{
    
    public:
    void print()
    {
        std::cout << "F" << std::endl;
    }
    
};
*/
int main()
{
    A a;
    A& ra = a;
    ra.print(); // expect A
    B b;
    ra = b;
    ra.print(); //still A becuase ra is still a reference to an A
    B& rb = b;
    rb.print(); //B
    C c;
    rb = c;
    rb.print(); //B: rb is a reference to a B, it cannot be re-bound by pointing it at a C
    B* pb = &c;
    pb->print();// C, even though the pointer is B*, the pointer can re-bind
    D d;
    pb = &d;
    pb->print(); //D because everyone below B has the virual print and the pointer rather than reference allows us to get the virtual effect 
    
    F f;
    F* pd = &f;
    pd->print(); //this generates an error with a diamond problem becasue the compiler doesn't know which path to resolve prints in
    
    return 0;
}