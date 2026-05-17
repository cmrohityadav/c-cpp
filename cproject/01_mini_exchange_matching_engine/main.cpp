#include<iostream>
#include"matchingEngine.hpp"
int main(){
    std::cout<<"Welcom to Mini Exchange Matching Engine"<<std::endl;

    MatchingEngine engine;

    while(1){
        std::cout << "--- EXCHANGE CONSOLE MENU ---\n";
        std::cout << "1. Place New Order\n";
        std::cout << "2. View Order Book (Market Depth)\n";
        std::cout << "3. View Trade History (Ledger)\n";
        std::cout << "4. Exit System\n";
        std::cout << "Choose option (1-4): ";

        int choice;
        std::cin>>choice;

        if(choice==4){
            std::cout<<"\nThanks for using Our Mini Exchange Matching Engine \n";
            break;
        }

        switch(choice){
            case 1:{
                int iClientId,iBuySell;
                double price;
                int qty;

                std::cout << "Enter Client UserID: "; std::cin >> iClientId;
                std::cout << "Enter Side (BUY- 1/SELL- 2): "; std::cin >> iBuySell;
                std::cout << "Enter Quantity: "; std::cin >> qty;
                std::cout << "Enter Price: "; std::cin >> price;
                
                
                engine.placeOrder(iClientId, iBuySell, price, qty);
                break;

            }
            case 2:
                engine.showOrderBook();
                break;
            case 3:
                engine.showTradeHistory();
                break;
            default:
                std::cout << "[ERROR] Invalid selection. Try again.\n\n"; 
        }
    }
    return 0;
}