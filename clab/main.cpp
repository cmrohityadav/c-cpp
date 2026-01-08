#include<iostream>

class Base{
    public:
    int x=10;
    void function(){
        std::cout<<"Printing using base class function"<<std::endl;
    }
};

class Derived: public Base{
    public:
    void function1(){
        std::cout<<"Output from derived class "<<std::endl;
        std::cout<<"Value of x : "<<x<<std::endl;
    }
};



int main(){

    Derived d;
    d.function();
    d.function1();

    Base b;
    b.function();
    return 0;
}