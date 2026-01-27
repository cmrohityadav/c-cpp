#include<iostream>
#include"scientific/scientific.hpp"


int main(){

    std::cout << "Scientific Calculator\n";
    std::cout << "Square(4) = " << scientific::square(4) << "\n";
    std::cout << "Cube(3) = " << scientific::cube(3) << "\n";

    return 0;
}