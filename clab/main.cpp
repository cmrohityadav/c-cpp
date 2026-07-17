#include<iostream>

auto add=[](int a ,int b){
    return a+b;
};

int main(){
    std::cout<<"\n"<<add(10,50);
}