#include<iostream>
enum class ORDER{
    SUCESS,
    FAILED,
    PENDING
};

enum Rohit{
    SUCESS
};

enum Rahul{
    FAILED,
    SUCESS
};

int main(){
     
    ORDER orderfail=ORDER::FAILED;
    Rohit my=SUCESS;
    

    if(orderfail==ORDER::FAILED){
        std::cout<<"Order Status: fail"<<std::endl;
    }
    
}