#include<iostream>
using namespace std;

int iAddTwentyTemp(int iTemp){
    return iTemp+20;

}


// declaration of function
void serveChai(int iCups);


//declaration with defination without parameter and return void type
void makeChai(){
    cout<<"Boiling water....adding tea leaves, strairing..."<<endl;

}


//default parameter
void printName(string sUserName ="Username"){
    cout<<sUserName<<endl;
}
int main()
{   //calling function and passing argument 
    int iTemperature=iAddTwentyTemp(30);
    cout<<iTemperature<<endl;

    serveChai(3);

    makeChai();

    printName("rohit_yadav");
    printName();

    return 0;
}

//defintion of function with parameter
    void serveChai(int iCup){
        cout<<"serving "<<iCup<<" of chai"<<endl;
    }