#include<iostream>
#include<basic/calculator.hpp>

int main(){
    std::cout<<"Basic Calculator"<<std::endl;

    std::cout<<"3 + 2 = "<<basic::add(3,2)<<std::endl;
    std::cout << "5 - 1 = " << basic::sub(5, 1) << "\n";
    return 0;
}