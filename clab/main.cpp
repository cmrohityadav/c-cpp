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

    Stock  jswObj("JSW",142.52,"S");

    jswObj.display();

    indicator(jswObj);

    Basket basketObj;
    basketObj.checkBasketStockPrice(jswObj);


    Stock adani;
    adani.display();

    Stock jswPower=jswObj;
    jswPower.display();

    Stock tcsPower("tcsPower",25.01,"S");
    Stock tcs("tcs",2225.02,"S");

    tcsPower=tcs;

    tcsPower.display();





    return 0;
}