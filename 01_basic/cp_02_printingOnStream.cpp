#include<iostream>
#include <limits>
int main(){

    std::cout<<"This is Standard Output using std::cout ->Insert data on Output Stream:- Terminal"<<std::endl;

    std::clog<<"std::clog: This is log"<<std::endl;

    std::cerr<<"std::cerr : This is error"<<std::endl;

    int mobile;

    std::cout<<"Enter your mobile number"<<std::endl;

    std::cin>>mobile;

    std::cout<<"Enter your full name: ";

    std::string fullName;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    
    std::getline(std::cin,fullName);

    std::cout<<"User Mobile Number: "<<mobile<<std::endl;

    std::cout<<"User Full Name: "<<fullName<<std::endl;


    return 0;
}