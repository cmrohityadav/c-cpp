#include<iostream>
#include<memory>
int main(){

    // std::unique_ptr<int>ptr(new int(100));
    std::unique_ptr<int>ptr=std::make_unique<int>(100);

    std::cout<<ptr.get()<<std::endl;
    std::cout<<*ptr<<std::endl;
    
    return 0;
}