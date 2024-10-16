#include <iostream>
#include <vector>
using namespace std;
class Chai
{
public:
    // data members(attributes)
    string sTeaName;
    int iServingCount;

    vector<string> vctIngredients;

    // member function
    void displayChaiDetails()
    {
        cout << "Tea Name :" << sTeaName << endl;
        cout << "Tea Servings :" << iServingCount << endl;

        cout << "Ingredients :" ;

        for (string sItemIngredient : vctIngredients)
        {
            cout << sItemIngredient << " , ";
        }
    }
};

int main()
{

    Chai objLemonChai;

    objLemonChai.sTeaName="Lemon Tea";
    objLemonChai.iServingCount=10;
    objLemonChai.vctIngredients={"water","sugar","chai patta"};

    objLemonChai.displayChaiDetails();


    cout<<endl<<endl;
    Chai objMilkTea;
    objMilkTea.sTeaName="Milk tea";
    objMilkTea.iServingCount=2;
    objMilkTea.vctIngredients={"milk","fresh milk","powder milk"};

    objMilkTea.displayChaiDetails();
    return 0;
}