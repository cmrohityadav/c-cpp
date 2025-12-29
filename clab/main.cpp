#include<iostream>
#include<string>

class OrderBook{
    public:
    int orderQty;
    int price;
    static std::string brokerName;

    OrderBook(int ordderQty,int price){
        this->orderQty=ordderQty;
        this->price=price;
    }
};

std::string OrderBook::brokerName="Rohit";
int main(){
    std::cout<<"Broker Name: "<<OrderBook::brokerName<<std::endl;

    OrderBook ob(100,10);

    std::cout<<ob.brokerName<<std::endl;

    OrderBook ob2(200,5);

    std::cout<<ob2.brokerName<<std::endl;


    return 0;
}