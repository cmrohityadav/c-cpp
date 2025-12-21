#include <iostream>
#include <string>

class Strategy {
public:
    int qty;
    double price;
    std::string userName;

    Strategy(int orderQty, double orderPrice, std::string userID) {
        qty = orderQty;
        price = orderPrice;
        userName = userID;
    }

    Strategy() = delete;  

    void Print() {
        std::cout << price << std::endl;
        std::cout << qty << std::endl;
        std::cout << userName << std::endl;
    }
};

int main() {
    Strategy s1(10, 50.2, "trader");
    s1.Print();
    return 0;
}
