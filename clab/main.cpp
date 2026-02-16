#include<iostream>
class Strategy{
  public:
  int amt;

  Strategy()=delete;

  Strategy(int amt){
    this->amt=amt;
    std::cout<<"Constructor called"<<std::endl;
  }

  Strategy(){
    this->amt=5;
    std::cout<<"Constructor called"<<std::endl;
  }
};
int main(){

  Strategy s;
  std::cout<<s.amt<<std::endl;
  return 0;
}