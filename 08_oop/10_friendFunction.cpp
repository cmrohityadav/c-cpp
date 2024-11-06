#include<iostream>
#include<vector>
#include<string>
using namespace std;


class Chai{
    private:
    string sTeaName;
    int iServing;
    vector<string>vct_sIngredients;

    public:
    Chai(string name,int serve):sTeaName(name),iServing(serve){}
    friend bool compareServings(const Chai &Chai1,const Chai &Chai2);
    void display()const{
        cout<<"tea name: "<<sTeaName<<endl;

    }
};
bool compareServings(const Chai &Chai1,const Chai &Chai2){
    return Chai1.iServing>Chai2.iServing;
}
int main()
{   
    
 Chai masalaChai("masala Chai",5);
 Chai gingerChai("Ginger Chai",14);

 masalaChai.display();
 gingerChai.display();

 if(compareServings(masalaChai,gingerChai)){
    cout<<"masala chai having MORE serving"<<endl;

 }else{
    cout<<"masala chai having LESS serving"<<endl;

 }
    return 0;
}
