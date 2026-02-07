#include <iostream>
using namespace std;


int main() {
   

   const int a=10;

    const int* ptr=&a;

    int* newValue=const_cast<int*>(ptr);

    *newValue=20; //// ❌ Undefined Behavior

    cout<<"value of a: "<<a<<endl; //10
    cout<<"value of newValue: "<<*newValue<<endl; //20

return 0;
}