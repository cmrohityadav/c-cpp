#include "stock.hpp"
#include<iostream>

Stock::Stock(std::string scrip,float prc,int qty){
    name=scrip;
    price=prc;
    this->quantity=qty;
}

void Stock::buy(int qty){
    std::cout<<"Buying : "<<this->name<<" Qty: "<<this->quantity<<" @"<<this->price<<std::endl;
    this->quantity+=qty;
}


void Stock::sell(int qty){
    std::cout<<"Selling : "<<this->name<<" Qty: "<<this->quantity<<" @"<<this->price<<std::endl;
    if(this->quantity<qty){
        std::cout<<"Check your qty"<<std::endl;
        return;
    }
    this->quantity-=qty;
}

void Stock::showInfo() const {
    std::cout << "Stock: " << name
              << " | Price: " << price
              << " | Quantity: " << quantity << std::endl;
}