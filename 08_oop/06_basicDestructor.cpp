#include<iostream>
#include<vector>
using namespace std;


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
    Chai lemonChaiCopy=lemonChai;
    lemonChaiCopy.displayChaiDetails();


    *lemonChai.sTeaName="modified lemon tea";
    cout<<"Here Modified the original object data member"<<endl;

    cout<<"lemon tea-----Original Object"<<endl;
    lemonChai.displayChaiDetails();
    
    cout<<"copied lemon tea-----Copied Object"<<endl;
    lemonChaiCopy.displayChaiDetails();
    return 0;
}
