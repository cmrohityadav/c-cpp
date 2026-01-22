#include<iostream>
class ParentStrategy{
    public:

    double order_qty;
    double price;

    ParentStrategy(double qty,double price):order_qty(qty),price(price){};
    
    void PriceStrategy(){
        std::cout<<"order_qty:\t"<<order_qty<<std::endl;
        std::cout<<"Price: \t"<<price<<std::endl;
    } 

    void SubmitStrategy(){
        std::cout<<"Submitting the order to the Exchange"<<std::endl;
    }


    protected:
    void ModifyStrategy(){
        std::cout<<"Modifying the strategy"<<std::endl;

    }


    private:
    void CancleStrategy(){
        std::cout<<"Cancel the Startegy "<<std::endl;
    }

};

class Strategy:public ParentStrategy{
    public:
    Strategy(double qty,double price):ParentStrategy(qty,price){};
    
    void CreateStrategy(){
        std::cout<<"Strategy creation is doing...."<<std::endl;
        SubmitStrategy();

        ModifyStrategy();

        //CancleStrategy(); //private member are not allow
    }
};
int main(){
    Strategy s(100,23.50);

    s.PriceStrategy();
    s.SubmitStrategy();
    s.CreateStrategy();

    //s.ModifyStrategy(); // protected member are not allow 

    //s.CancleStrategy();  //private member are not allow
    return 0;
    
}