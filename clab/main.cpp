#include<iostream>

class Animal{
  public:
  void Speak(){
    std::cout<<"Speak"<<std::endl;
  }
};
class Dog: public Animal{
  public:
  void Speak(){
    std::cout<<"Bhowwwwwwwwwwwwww"<<std::endl;
  }
};
class Cat:public Animal{
  public:
  void Speak(){
    std::cout<<"Meowwwwwwwwwwwww"<<std::endl;
  }
};
int main(){

  Animal a;
  a.Speak();

  Dog d;
  d.Speak();

  Cat c;
  c.Speak();

  Animal* pA=new Animal();
  pA->Speak();//Speak

  Animal* pAD=new Dog();
  pAD->Speak(); //Speak

  Dog* pDD=new Dog();
  pDD->Speak(); //Bhowwwwwwwwwwwwww





  return 0;
}