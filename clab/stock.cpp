#include "stock.hpp"
#include <cstring>
#include<iomanip>
#include<iostream>
Stock::Stock(const char* scrip_name,double price_,const char* bs):price(price_){
    std::strncpy(scrip,scrip_name,sizeof(scrip)-1);
   std::strncpy(buysell,bs,sizeof(buysell)-1);
   buysell[sizeof(buysell) - 1] = '\0';
}

Stock::Stock(){
    std::strncpy(this->scrip, "No", sizeof(this->scrip));
    this->price=0;
    std::strncpy(this->buysell,"N",sizeof(this->buysell));
}

Stock::Stock(const Stock& other){
    this->price=other.price;
    
    std::strncpy(this->scrip, other.scrip, sizeof(this->scrip) - 1);
    this->scrip[sizeof(this->scrip) - 1] = '\0';

    std::strncpy(this->buysell, other.buysell, sizeof(this->buysell) - 1);
    this->buysell[sizeof(this->buysell) - 1] = '\0';

}

void Stock::display() const
{
    std::cout << "====================================\n";

    std::cout << "  STOCK INFORMATION\n";

    std::cout << "====================================\n";

    std::cout << std::left;

    std::cout << std::setw(15)
              << "Symbol"
              << ": "
              << scrip
              << '\n';

    std::cout << std::setw(15)
              << "Price"
              << ": "
              << price
              << '\n';

    std::cout << std::setw(15)
              << "Side"
              << ": "
              << buysell
              << '\n';

    std::cout << "====================================\n";
}