#include<iostream>
#include<string>
class Strategy{
    private:
    int orderQty;
    public:
    static std::string companyName;

    Strategy(int Qty):orderQty(Qty){
        std::cout<<"Constructor called"<<std::endl;
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

int main(){
    std::cout<<Strategy::companyName<<std::endl;
    Strategy obj(100);
    
    obj.DisplayQty();
    obj.DisplayCompanyName();
    Strategy::DisplayCompanyName();
    return 0;
}