#include <iostream>
using namespace std;

class Order{
    public:
    virtual void submitOrder()=0;
    virtual void changeOrder(){
        cout<<"Change order using Parent"<<endl;
    }
};

class order1:public Order{
   void changeOrder(){
        cout<<"Change order using Parent"<<endl;
    } 
};
int main() {
   
   
}