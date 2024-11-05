#include<iostream>
#include<vector>
using namespace std;

class Chai{
    public:
    string sTeaName;
    int iServing;
    vector<string>vct_sIngredients;
//deligating Constructor
Chai(string name):Chai(name,1,{"water","tea leaves"}){}

    //main constructor
    Chai(string name,int serve,vector<string>ing){

        sTeaName=name;
        iServing=serve;
        vct_sIngredients=ing;
        cout<<"main constructor called!"<<endl;
    }

    void displayChaiDetails()
    {
        cout << "Tea Name :" << sTeaName << endl;
        cout << "Tea Servings :" << iServing << endl;

        cout << "Ingredients :" ;

        for (string sItemIngredient : vct_sIngredients)
        {
            cout << sItemIngredient << " , ";
        }
    }

};

int main()
{
    Chai quickChai("Quick chai");
    quickChai.displayChaiDetails();
    return 0;
}
