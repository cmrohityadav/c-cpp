#include<iostream>

class Number{
public:
    int value;

    Number(int n):value(n){}

    // 😈 Masti assignment
    Number& operator=(const Number &obj){
        this->value = obj.value * 2;   // double kar diya
        return *this;
    }
};

int main(){
    Number num1(10);
    Number num2(20);

    num1 = num2;

    std::cout<<num1.value<<std::endl;
}