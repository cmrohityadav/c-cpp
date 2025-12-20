#include<iostream>
class Strategy{
    public:
    int qty;
    int price;
    std::string userName;

    Strategy(){
        qty=10;
        price=10.5;
        userName="TraderRohit";
    }

};

int main(){
    Strategy s;
    std::cout<<s.price<<std::endl;
    std::cout<<s.qty<<std::endl;
    std::cout<<s.userName<<std::endl;
    return 0;
}