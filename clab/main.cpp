#include<iostream>
#include<string>
class Strategy{
    private:
    int orderQty;
    static int strategyCount;
    public:
    static std::string companyName;

    Strategy(int Qty):orderQty(Qty){
        std::cout<<"Constructor called"<<std::endl;
    }

    void PlaceOrder(){
        std::cout<<"Placing the order in the market"<<std::endl;
        strategyCount++;
    }

    static void DisplayTotalStrategies(){
        std::cout<<"Total count of strategy\t"<<strategyCount<<std::endl;
    }

    void DisplayQty(){
        std::cout<<"OrderQty:\t"<<orderQty<<std::endl;
    }

    static void DisplayCompanyName(){
        //we can't able to use non-static member inside the static function
        std::cout << "Company:\t" << companyName << std::endl;
    }
};

std::string Strategy::companyName="rohit pvt ltd";
int Strategy::strategyCount=0;

int main(){
    std::cout<<Strategy::companyName<<std::endl;
    Strategy obj(100);
    
    obj.DisplayQty();
    obj.DisplayCompanyName();
    Strategy::DisplayCompanyName();


    Strategy twoleg(200);
    twoleg.PlaceOrder();

    Strategy fourleg(400);
    fourleg.PlaceOrder();

    Strategy::DisplayTotalStrategies();
    
    return 0;
}