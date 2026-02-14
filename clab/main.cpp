#include<iostream>

class Acc{
  int money;

  public:
  void setMoney(int m){
    if(m<0){
      std::cout<<"Hey Invalid amount"<<std::endl;
    }else{
      money=m;
      std::cout<<"Hey Invalid amount"<<std::endl;
    }
    
  }
};
int main(){

  Acc rohit;

  rohit.setMoney(-10);
  

  return 0;
}