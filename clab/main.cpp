#include<iostream>

int main(){
    double salary[3]{10.5,11.3,12.5};

    for(int i{0};i<3;i++){
        std::cout<<*(salary+i)<<std::endl;
    }

    return 0;
}