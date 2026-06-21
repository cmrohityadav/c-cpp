#include<iostream>
#include <limits>
int main(){

    int qty;
    while(true){
        std::cout<<"Enter Quantity to BUY: ";
        std::cin>>qty;

        if(std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(
               std::numeric_limits<std::streamsize>::max(), 
               '\n'
            );
            std::cout<<"Please Enter a valid number"<<std::endl;
        }else{
            break;
        }
    }
    std::cout<<"Qty: "<<qty<<std::endl;
}