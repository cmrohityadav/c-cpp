#ifndef MATCHING_ENGINE
#define MATCHING_ENGINE
#include<map>
#include <list>
#include <vector>

struct Order{
    int orderId;
    int clientId;
    short buysell; // buy:1, sell:2
    double price;
    int quantity;
};

struct TradeLog{
    int buyerId;
    int sellerId;
    int quantity;
    double price;
};

class MatchingEngine{
private:
    // High to Low for BIDS
    std::map<double,std::list<Order>,std::greater<double>>bidsMap;

    // Low to High for ask
    std::map<double,std::list<Order>>asksMap;

    std::vector<TradeLog>tradeHistory;

    int orderNumber=1000;

public:

    void placeOrder(int clientId,int buySell,double price,int qty);
    
    void showOrderBook()const;

    void showTradeHistory()const;

};





#endif
