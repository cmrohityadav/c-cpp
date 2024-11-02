#include<iostream>
#include<vector>
using namespace std;


class Chai{
    public:
    string sTeaName;
    int iServingCount;
    vector<string>vct_sIngredients;

    //default constructor
    Chai(){
        cout<<"Constructor is called "<<endl;
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
    return 0;
}
