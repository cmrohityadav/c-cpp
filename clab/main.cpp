#include <iostream>
using namespace std;

class Base {
public:
    virtual void show(){
    cout<<"This is the base class"<<endl;
   }
};

class Derived:public Base{
    public:
    void show(){
        cout<<"This is the derived class"<<endl;
    }
};

void Excute(Base& obj){
    obj.show();
}

int main() {
   
   Derived objDerived;
   Excute(objDerived);
}