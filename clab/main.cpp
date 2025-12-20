#include<iostream>
class Strategy{
    public:
    int qty;
    double price;
    std::string userName;

    Strategy(int orderQty,double orderPrice,std::string userID){
       qty=orderQty;
       price=orderPrice;
       userName=userID;
    }

};

int main(){
    Strategy s(10,10.5,"traderrohit");
    std::cout<<s.price<<std::endl;
    std::cout<<s.qty<<std::endl;
    std::cout<<s.userName<<std::endl;
    return 0;
}