
#ifndef STOCK_HPP
#define STOCK_HPP

class Stock{
private:
    char scrip[10];
    double price;
    char buysell[2];

public:
    Stock(const char* scrip_name,double price_,const char* bs);

    Stock();

    Stock(const Stock& other);

    void display() const;
    friend void indicator(const Stock& obj);

    friend class Basket;
};

#endif
