#include<iostream>

auto add=[](int a ,int b) -> int{
    return a+b;
};

int main(){
    std::cout<<"\n"<<add(10,50);
}