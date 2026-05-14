#ifndef STOCK_HPP
#define STOCK_HPP

#include <string>

class Stock {
private:
    std::string name;
    float price;
    int quantity;

public:
    Stock(std::string n, float p, int q);

    void buy(int qty);
    void sell(int qty);
    void updatePrice(double newPrice);
    void showInfo() const;
};

#endif