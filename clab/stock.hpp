
#ifndef STOCK_HPP
#define STOCK_HPP

class Stock{
    char scrip[10];
    double price;
    char buysell[2];

public:
    Stock(const char* scrip_name,double price_,const char* bs);

    void display() const;
};

#endif
