#include<iostream>
#include<array>
int main(){

    std::array<int,5>strikePrice={123,456,789,147,258};
    
    std::cout<<"Accessing  using [0]: "<<strikePrice[0]<<std::endl;

    std::cout<<"Accessing  using At 2: "<<strikePrice.at(2)<<std::endl;
    // std::cout<<"Accessing  using At 10: "<<strikePrice.at(10)<<std::endl;

    std::cout<<"Accessing  front: "<<strikePrice.front()<<std::endl;

    std::cout<<"Accessing  back: "<<strikePrice.back()<<std::endl;

    std::cout<<"Size : "<<strikePrice.size()<<std::endl;

    std::cout<<"Empty : "<<strikePrice.empty()<<std::endl;

    std::array<int,5>StrikeCopy;

    StrikeCopy=strikePrice;

    std::cout<<"Accessing  using [0]: "<<StrikeCopy[0]<<std::endl;

    std::cout<<"Iteration using loop"<<std::endl;

    for(int i=0;i<StrikeCopy.size();i++){
        std::cout<<StrikeCopy.at(i)<<" ";
    }


    std::cout<<"\nIteration using modern"<<std::endl;
    for(int item:strikePrice){
        std::cout<<item<<" ";
    }

    std::cout<<"\nIteration using auto iterator"<<std::endl;

    for(auto p_itr=strikePrice.begin();p_itr!=strikePrice.end();++p_itr){
        std::cout<<*p_itr<<" ";
    }

    std::cout<<"\nIteration using create iterator"<<std::endl;

    std::array<int,5>::iterator p_itr;
    p_itr=strikePrice.begin();
    

    while(p_itr!=strikePrice.end()){
        std::cout<<*p_itr<<" ";
        ++p_itr;
    }
    std::cout<<"\n"<<std::endl;
    
    return 0;
}