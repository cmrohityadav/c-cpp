#include<iostream>
#include<vector>
using namespace std;


class Chai{
    public:
    string sTeaName;
    int iServingCount;
    vector<string>vct_sIngredients;

    //default constructor
    //jaise bhi ek object banega waise hi yeh function:constructor call hoga
    // used to set initial value of data members
    Chai(){
        sTeaName="Unknown Tea";
        iServingCount=1;
        vct_sIngredients={"water","tea leaf"};
        cout<<"constructor call"<<endl;
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
    Chai lemonChai;
    lemonChai.displayChaiDetails();

    Chai gingerChai;
    return 0;
}
