#include<iostream>
#include<vector>
using namespace std;


class Chai{
    public:
    string sTeaName;
    int iServingCount;
    vector<string>vct_sIngredients;

    //paramter constructor
    
    Chai(string name,int serve,vector<string>vct_sItems){
       sTeaName=name;
       iServingCount=serve;
       vct_sIngredients=vct_sItems;
       cout<<"param constructor called"<<endl;
    }

void displayChaiDetails()
    {
        cout << "Tea Name :" << sTeaName << endl;
        cout << "Tea Servings :" << iServingCount << endl;

        cout << "Ingredients :" ;

        for (string sItemIngredient : vct_sIngredients)
        {
            cout << sItemIngredient << " , ";
        }
    }
};
int main()
{
    Chai lemonChai("Lemon tea",2,{"water","lemon","salt"});
    lemonChai.displayChaiDetails();

    
    return 0;
}
