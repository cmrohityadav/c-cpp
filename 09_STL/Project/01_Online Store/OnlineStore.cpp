#include<iostream>
#include<vector>
#include<deque>
#include<list>
#include<set>
#include<map>
#include<ctime>
#include<unordered_set>
#include<unordered_map>

using namespace std;

struct Product{
    int iProductID;
    string sName;
    string sCategory;

};

struct Order{
    int iOrderID;
    int iProductID;
    int iQuantity;
    string sCustomerID;
    time_t orderDate;
};



int main()
{
    vector<Product>vct_products={
        {101,"laptop","Electronic"},
        {102,"SmartPhone","Electronic"},
        {103,"Coffe Maker","Kitchen"},
        {103,"Blender","Kitchen"},
        {103,"Desk lamp","Home"},
    };

    deque<string>recentCustomers={"C001","C002","C003"};
    
    recentCustomers.push_back("C004");
    recentCustomers.push_front("C005");

    list<Order>orderHistory;
    orderHistory.push_back({1,101,1,"C001",time(0)});
    orderHistory.push_back({2,102,2,"C002",time(0)});
    orderHistory.push_back({3,103,1,"C003",time(0)});

    set<string>categories;

    for(const auto &product:vct_products){
        categories.insert(product.sCategory);
    }

    map<int,int>productStock={
        {101,10},
        {102,100},
        {103,108},
        {104,15},
        {105,20},
        {106,50},
    };

    multimap<string,Order>customerOrders;
    for(const auto &order:orderHistory){
        customerOrders.insert({order.sCustomerID,order});
    }

    unordered_map<string,string>customerData={
        {"C001","Rohit"},
        {"C002","Rahul"},
        {"C003","Yadav"},
        {"C004","Van"},
        {"C003","Dhana"},
    };

    unordered_set<int>uniqueProductIDs;
for(const auto &product:vct_products){
    uniqueProductIDs.insert(product.iProductID);
}

    return 0;
}
