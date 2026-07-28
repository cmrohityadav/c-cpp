#include<iostream>
enum class ORDER{
    SUCESS,
    FAILED,
    PENDING
};

int main(){
     
    ORDER orderfail=ORDER::FAILED;

    

    if(orderfail==ORDER::FAILED){
        std::cout<<"Order Status: fail"<<std::endl;
    }
    
}