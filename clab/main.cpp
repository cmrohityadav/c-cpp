#include<iostream>
#include"stock.hpp"
int main(){

    Stock s1("TCS",1250.30,30);

    s1.buy(100);
    s1.sell(50);
    s1.showInfo();

    Stock s2("JSW",150.30,100);
    s2.sell(50);
    s2.showInfo();


    Stock s3("JPP",14,10);
    s3.sell(500);
    s3.showInfo();
    return 0;
}