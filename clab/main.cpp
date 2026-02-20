#include<iostream>
class A{
    public:
    int x;
    A(int a=64):x(a){}
};

class B:public A{};
// class C: public A{};

class D: public B{};
int main(){

    D d1;
    std::cout<<d1.x<<std::endl;
    

    return 0;
}