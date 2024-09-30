#include<iostream>
#include<string>
using namespace std;
/*
    Write a program that checks if the user wants to order Green Tea. If the user types "Green Tea," the program should confirm their order.
*/
int main()
{
    
    string sTeaOrder;
    cout<<"Enter your tea order\n";
    getline(cin,sTeaOrder);

    if(sTeaOrder=="Green tea"){
        cout<<"you have order green tea"<<endl;
    }
    


    return 0;
}
