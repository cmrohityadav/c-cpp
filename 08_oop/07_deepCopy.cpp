#include<iostream>
#include<vector>
using namespace std;
/*
Deep Copy
A deep copy duplicates not only the top-level values of the object but also creates a separate copy of any dynamic memory it points to. 
This ensures that the copied object has its own memory allocation, and changes to one object’s data won’t affect the other.
*/

class Chai{
    public:
    string *sTeaName;
    int iServingCount;
    vector<string>vct_sIngredients;

    //copy constructor
    
    Chai(string name,int serve,vector<string>vct_sItems){
       sTeaName=new string(name);
       iServingCount=serve;
       vct_sIngredients=vct_sItems;
       cout<<"param constructor called"<<endl;
    }

    Chai(Chai& kuchhbhi){
        sTeaName=new string(*kuchhbhi.sTeaName);
        iServingCount=kuchhbhi.iServingCount;
        vct_sIngredients=kuchhbhi.vct_sIngredients;
        cout<<"Deep copy  constructor called"<<endl;

    }
    //destructor
    ~Chai(){
        delete sTeaName;
        cout<<"Destructor called"<<endl;

    }

void displayChaiDetails()
    {
        cout << "Tea Name :" << *sTeaName << endl;
        cout << "Tea Servings :" << iServingCount << endl;

        cout << "Ingredients :" ;

        for (string sItemIngredient : vct_sIngredients)
        {
            cout << sItemIngredient << " , ";
        }

        cout<<endl;
    }
};
int main()
{
    Chai lemonChai("Lemon tea",2,{"water","lemon","salt"});
    lemonChai.displayChaiDetails();

    //copy the object
    cout<<"Here started copying the Original Object"<<endl;
    Chai lemonChaiCopy=lemonChai;
    lemonChaiCopy.displayChaiDetails();

    cout<<"Here Modified the original object data member"<<endl;

    *lemonChai.sTeaName="modified lemon tea";

    cout<<"Original Object:: lemon tea-----------"<<endl;
    lemonChai.displayChaiDetails();
    
    cout<<"Copied Object:: lemon tea-----------"<<endl;
    lemonChaiCopy.displayChaiDetails();
    return 0;
}
