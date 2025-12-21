#include <iostream>
#include <string>

using namespace std;

class OrderBuilder
{
public:
    OrderBuilder(string name, int id)
    {
        exchangeName = name;
        exchangeId = id;
    }

    int exchangeId;
    string exchangeName;
};

class Strategy
{
    double orderQty;
    double price;
    string userName;
    OrderBuilder* ob;

public:
    Strategy(double qty, double prc, string name)
        : orderQty(qty), price(prc), userName(name)
    {
        cout << "Inside constructor" << endl;
        OrderBuilder* obj = new OrderBuilder("NSE", 107);
        ob = obj;
    }

    ~Strategy()
    {
        cout << "Destructor called" << endl;
        delete ob;
    }

    void PrintStrategy()
    {
        cout << "OrderQty:\t" << orderQty << endl;
        cout << "Price:\t\t" << price << endl;
        cout << "UserName:\t" << userName << endl;
        cout << "ExchangeName:\t" << ob->exchangeName << endl;
    }
};

int main()
{
    Strategy* obj1 = new Strategy(10, 100.0, "rohit");
    obj1->PrintStrategy();

    Strategy obj2(*obj1);   // DEFAULT COPY CONSTRUCTOR (SHALLOW COPY)

    delete obj1;            

    obj2.PrintStrategy();  

    return 0;
}
