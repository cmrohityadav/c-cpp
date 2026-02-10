#include<iostream>

int main(){

  int a=10, b=40;

  std::cout<<a<<std::endl;

  int& ref=a;

  ref=b;

  std::cout<<ref<<std::endl;

  std::cout<<"after a: "<<std::endl;
  std::cout<<a<<std::endl;
  

  return 0;
}