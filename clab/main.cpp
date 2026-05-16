#include"stock.hpp"
#include "basket.hpp"
#include<iostream>
void indicator(const Stock& stockObj){
    if(stockObj.price>73){
        std::cout<<"Buy at ur risk"<<std::endl;
    }else{
        std::cout<<"Dont buy now"<<std::endl;
    }
}
int main(){

    Stock  jswObj("7774",142.52,"S");

    jswObj.display();

    indicator(jswObj);

    Basket basketObj;
    basketObj.checkBasketStockPrice(jswObj);

    return 0;
}