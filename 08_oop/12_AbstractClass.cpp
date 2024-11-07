#include<iostream>
using namespace std;
//This is the Abstract Class
class Tea{
    public:
    virtual void prepareIngredients()=0; //pure virtual function
    virtual void brew()=0;
    virtual void serve()=0;

    void makeTea(){
        prepareIngredients();
        brew();
        serve();

    }
};

//Derived class
class GreenTea:public Tea{
    public:
    void prepareIngredients()override{
        cout<<"green leaves and water is ready"<<endl;

    }
    void brew() override{
        cout<<"Green Tea brewed"<<endl;
    }

    void serve() override{
        cout<<"Green Tea Served"<<endl;
    }
};

class MasalaTea:public Tea{
    public:
    void prepareIngredients()override{
        cout<<"green leaves and water is ready along with masala"<<endl;

    }
    void brew() override{
        cout<<"Masala Tea brewed"<<endl;
    }

    void serve() override{
        cout<<"Masala Tea Served"<<endl;
    }
};

int main()
{
    
    GreenTea greenTea;
    MasalaTea masalaTea;

    greenTea.makeTea();
    masalaTea.makeTea();
    
    return 0;
}
