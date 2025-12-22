#include <iostream>
#include <string>

using namespace std;

class OrderBuilder
{
public:
    int exchangeId;
    string exchangeName;

    OrderBuilder(string name, int id)
        : exchangeId(id), exchangeName(name)
    {
    }

    // Copy constructor
    OrderBuilder(const OrderBuilder& other)
        : exchangeId(other.exchangeId),
          exchangeName(other.exchangeName)
    {
    }
};

class Strategy
{
    double orderQty;
    double price;
    string userName;
    OrderBuilder* ob;

public:
    // Constructor
    Strategy(double qty, double prc, string name)
        : orderQty(qty), price(prc), userName(name)
    {
        cout << "Inside constructor" << endl;
        ob = new OrderBuilder("NSE", 107);
    }

    //  Deep copy constructor
    Strategy(const Strategy& other)
        : orderQty(other.orderQty),
          price(other.price),
          userName(other.userName)
    {
        cout << "Inside deep copy constructor" << endl;
        ob = new OrderBuilder(*other.ob); // DEEP COPY
    }

    // Destructor
    ~Strategy()
    {
        cout << "Destructor called" << endl;
        delete ob;
    }

    void PrintStrategy() const
    {
        cout << "OrderQty:\t" << orderQty << endl;
        cout << "Price:\t\t" << price << endl;
        cout << "UserName:\t" << userName << endl;
        cout << "ExchangeName:\t" << ob->exchangeName << endl;
        cout << "ExchangeId:\t" << ob->exchangeId << endl;
        cout << "-------------------------" << endl;
    }
};

int main()
{
    Strategy* obj1 = new Strategy(10, 100.0, "rohit");
    obj1->PrintStrategy();

    Strategy obj2(*obj1);   // ✅ DEEP COPY

    delete obj1;            // obj2 is still valid

    obj2.PrintStrategy();  

    return 0;
}
