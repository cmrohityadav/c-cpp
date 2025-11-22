#include<iostream>
#include<iterator>

int main(){
    int fruits[]={1,2,3,4,5,6};

    int count {std::size(fruits)};


    std::cout<<count<<std::endl;
    return 0;
}