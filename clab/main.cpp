#include <iostream>
using namespace std;


int main() {
   
    double amount {10.56};
    int salary = (int)amount;

    std::cout<<salary<<std::endl;

    double tcs_price=2500.56;

    


    int a=10;

    const int* ptr=&a;

    int* newValue=const_cast<int*>(ptr);

    *newValue=20;

    std::cout<<*newValue<<std::endl;
    std::cout<<a<<std::endl;




   
}