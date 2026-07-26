#include<iostream>
#include<cstring>
int main(){

    char name[]="rohit";

    char temp[6];

    std::memcpy(&temp,&name,2); //sirf 2 byte copy hoga

    std::cout<<temp<<std::endl;
}