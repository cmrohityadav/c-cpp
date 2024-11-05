#include<iostream>
#include<vector>
using namespace std;

class Chai{
    private:
    string sTeaName;
    int iServing;
    vector<string>vct_sIngredients;

    public:

    Chai(){
        sTeaName="Unknown tea";
        iServing=1;
        vct_sIngredients={"Water","tea leaves"};
    }

    Chai(string sName,int iServ,vector<string>vct_in){

        sTeaName=sName;
        iServing=iServ;
        vct_sIngredients=vct_in;

    }

    //getter::to get private member access
    string getTeaName(){
        return sTeaName;
    }


    //setter
    void setTeaName(string name){
        sTeaName=name;
    }

    //getter for serving
    int getServings(){
         return iServing;
    }
    //setter for serving
    void setServing(int serv){
        iServing=serv;
    }

    //getter for Ingredients
    vector<string> getIngredients(){

        return vct_sIngredients;
    }

    //setter for Ingredients
    void setIngredients(vector<string>ing){
        vct_sIngredients=ing;
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
    Chai chai;

    chai.setTeaName("Ginger tea");
    
    string chaiName=chai.getTeaName();
    cout<<chaiName<<endl;
    return 0;
}
