#include<iostream>
#include<vector>
using namespace std;
// Shallow Copy
/*
A shallow copy duplicates the top-level values of the original object, including any pointers, but does not create copies of the memory they point to. 
This means both the original and copied object point to the same memory location for dynamic data, 
which can lead to problems if one modifies or deletes this memory.
*/

class Chai{
    public:
    string sTeaName;
    int iServingCount;
    vector<string>vct_sIngredients;

    //copy constructor
    
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

        cout<<endl;
    }
};
int main()
{
    Chai lemonChai("Lemon tea",2,{"water","lemon","salt"});
    lemonChai.displayChaiDetails();

    //copy the object
    cout<<"Here copy object------"<<endl;
    Chai lemonChaiCopy=lemonChai;
    lemonChaiCopy.displayChaiDetails();

    cout<<"Here Modified the original object data member"<<endl;
    lemonChai.sTeaName="modified lemon tea";

    cout<<"Original Object::lemon tea----------"<<endl;
    lemonChai.displayChaiDetails();
    
    cout<<"Copied Object::lemon tea------------"<<endl;
    lemonChaiCopy.displayChaiDetails();
    return 0;
}
