#include<iostream>
using namespace std;
/*
    Write a program that lets the user select a tea type from a menu. Use a switch statement to display the price based on the selected tea:* Green Tea: $2
Black Tea: $3
Oolong Tea: $4
*/
int main()
{
    int iChoice;
    double dPrice;
    cout<<"Select your tea\n";
    cout<<"1. Green tea\n 2. Lemon tea\n 3. oolong tea\n Enter your choice as per above number"<<endl;
    cin>>iChoice;

    switch(iChoice){

        case 1:
        {
            dPrice=2.0;
            cout<<"You Select Green Tea. Price : "<<dPrice<<endl;
            break;
        }
        case 2:
        {
            dPrice=3.0;
            cout<<"You Select Leamon. Price : "<<dPrice<<endl;
            break;
        }
        case 3:
        {
            dPrice=4.0;
            cout<<"You Select oolong. Price : "<<dPrice<<endl;
            break;
        }
        default:
        {
            cout<<"Invalid Choice"<<endl;
        }


    }
    return 0;
}
