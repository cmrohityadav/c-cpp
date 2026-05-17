#include"matchingEngine.hpp"
#include<iostream>
#include <iomanip>
#include <cstdint>
void MatchingEngine::placeOrder(int clientId,int buySell,double price,int qty){
    orderNumber++;

    Order newOrderObj={};
    newOrderObj.orderId=orderNumber;
    newOrderObj.clientId=clientId;
    newOrderObj.buysell=buySell;
    newOrderObj.price=price;
    newOrderObj.quantity=qty;

    std::cout << "\n[SYSTEM] Processing Order " << newOrderObj.orderId << "...\n";

    if(buySell==1){ 
        //BUY
        while(newOrderObj.quantity>0 && !asksMap.empty()){
            auto itr_bestAskPrice=asksMap.begin();
            if(newOrderObj.price>=itr_bestAskPrice->first){
                auto& bestAskOrderListAtPrice=itr_bestAskPrice->second;
                while(!bestAskOrderListAtPrice.empty() && newOrderObj.quantity>0){
                    auto& passiveOrder=bestAskOrderListAtPrice.front();
                    int fillQty=std::min(newOrderObj.quantity,passiveOrder.quantity);

                    //here trade happening
                    TradeLog tradeLogObj={0};
                    tradeLogObj.buyerId=clientId;
                    tradeLogObj.sellerId=passiveOrder.clientId;
                    tradeLogObj.price=passiveOrder.price;
                    tradeLogObj.quantity=fillQty;
                    tradeHistory.push_back(tradeLogObj);

                    std::cout << ">> [ALERT] TRADE MATCHED! " << fillQty << " Qty @ " << passiveOrder.price << " (" << newOrderObj.clientId << " bought from " << passiveOrder.clientId << ")\n";

                    passiveOrder.quantity-=fillQty;
                    newOrderObj.quantity-=fillQty;
                    
                    if(passiveOrder.quantity==0){
                        bestAskOrderListAtPrice.pop_front();
                    }
                }
                if(bestAskOrderListAtPrice.empty()){
                   asksMap.erase(itr_bestAskPrice); // Price level zero cleanup
                }

            }else{
                break; //here no matching happen so we place order in bids
            }
        }
        if(newOrderObj.quantity>0) bidsMap[newOrderObj.price].push_back(newOrderObj);

    }else{
        //SELL

    }

   std::cout << "[SYSTEM] Order processing completed.\n"; 
}

void MatchingEngine::showOrderBook()const{
    std::cout << "\n==================================================\n";
    std::cout << "            LIVE MARKET DEPTH (ORDER BOOK)        \n";
    std::cout << "==================================================\n";
    std::cout << "     BIDS (BUY)          |         ASKS (SELL)    \n";
    std::cout << "-------------------------+------------------------\n";
    std::cout << std::left << std::setw(8) << "Orders" << std::setw(8) << "TotalQty" << std::setw(9) << "Price"
                  << "|"
                  << std::left << std::setw(9) << " Price" << std::setw(8) << "TotalQty" << std::setw(8) << "Orders" << "\n";
        std::cout << "-------------------------+------------------------\n";

        // Bids structures map se read karenge
        std::vector<std::string> bidRows;
        for (const auto& [price, list] : bidsMap) {
            uint32_t totalPriceQty = 0;
            uint32_t orderCount = 0;
            for (const auto& ord : list) {
                if (ord.quantity > 0) { // Sirf wahi dikhao jiska qty > 0 hai
                    totalPriceQty += ord.quantity;
                    orderCount++;
                }
            }
            if (orderCount > 0) {
                char buf[100];
                snprintf(buf, sizeof(buf), "%-8u %-8u %-8.2f", orderCount, totalPriceQty, price);
                bidRows.push_back(buf);
            }
        }

        // Asks structures map se read karenge
        std::vector<std::string> askRows;
        for (const auto& [price, list] : asksMap) {
            uint32_t totalPriceQty = 0;
            uint32_t orderCount = 0;
            for (const auto& ord : list) {
                if (ord.quantity > 0) {
                    totalPriceQty += ord.quantity;
                    orderCount++;
                }
            }
            if (orderCount > 0) {
                char buf[100];
                snprintf(buf, sizeof(buf), " %-8.2f %-8u %-8u", price, totalPriceQty, orderCount);
                askRows.push_back(buf);
            }
        }

        size_t maxRows = std::max(bidRows.size(), askRows.size());
        for (size_t i = 0; i < maxRows; ++i) {
            if (i < bidRows.size()) std::cout << bidRows[i];
            else std::cout << std::left << std::setw(25) << " ";
            
            std::cout << "|";
            
            if (i < askRows.size()) std::cout << askRows[i];
            std::cout << "\n";
        }

        if (maxRows == 0) {
            std::cout << "          [ MARKET IS CURRENTLY ILLIQUID ]        \n";
        }
        std::cout << "==================================================\n\n";

}

void MatchingEngine::showTradeHistory()const{
     std::cout << "\n==================================================\n";
        std::cout << "                    TRADE LEDGER                  \n";
        std::cout << "==================================================\n";
        if (tradeHistory.empty()) {
            std::cout << "            No trades executed in this session.   \n";
        } else {
            for (const auto& trade : tradeHistory) {
                std::cout << "[MATCH] " << trade.buyerId << " bought " << trade.quantity
                          << " shares from " << trade.sellerId<< " @ Rs." << trade.price << "\n";
            }
        }
        std::cout << "==================================================\n\n";
}