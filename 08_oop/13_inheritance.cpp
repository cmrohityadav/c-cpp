#include<iostream>
using namespace std;


// Base/main/parent class

class Tea{

    protected:
    string sTeaName;
    int iServing;

    public:
    Tea(string sName,int iServe):sTeaName(sName),iServing(iServe){
        cout<<"Tea constructor called "<<sTeaName<<endl;
    }

    virtual  void brew() const{
        cout<<"Brewing "<<sTeaName<<" with generic method "<<endl;
    }

    virtual  void serve() const{
        cout<<"Serving "<<iServing<<" cup of tea with generic method "<<endl;
    }

    virtual ~Tea(){
        cout<<"Tea destructor called for "<<sTeaName<<endl;
    }

};

class GreenTea:public Tea{
    public:
    GreenTea(int iServe):Tea("Green tea",iServe){
        cout<<"Green tea constructor called"<<endl;
    }

    void brew()const override{
        cout<<"Brewing"<<sTeaName<<" by steeping green ltea leaves"<<endl;
    }
    ~GreenTea(){
        cout<<"Green tea destructor called"<<endl;
    }
};

class MasalaTea:public Tea{
    public:
    MasalaTea(int iServe):Tea("Masal Chai",iServe){
                cout<<"Masala tea constructor called"<<endl;

    }
     void brew()const override final{
        cout<<"Brewing"<<sTeaName<<"with species with milk masala tea leaves"<<endl;
    }
    ~MasalaTea(){
        cout<<"Masal tea destructor called"<<endl;
    }

};
/*
class SpicyMasalaTea:public MasalaTea{
    public:
     void brew()const override{
        cout<<"Brewing"<<sTeaName<<"with species with milk masala tea leaves"<<endl;
    }

}
*/

int main()
{
    Tea * teaOne=new GreenTea(2);
    Tea * teaTwo=new MasalaTea(3);
    teaOne->brew();
    teaTwo->serve();

   teaTwo->brew();
   teaTwo->serve();

   delete teaOne;
   delete teaTwo;

    return 0;
}
