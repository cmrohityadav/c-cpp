#include<iostream>
using namespace std;
/*
    Write a program that checks if a tea shop is open. If the current hour (input by the user) is between 8 AM and 6 PM, the shop is open; otherwise, it’s closed
*/
int main()
{
    int iHour;
    cout<<"Enter the current hour (0:24)\n";
    cin>>iHour;

    if(iHour>=8 && iHour<=18){
        cout<<"Tea shop is OPEN"<<endl;

    }else{
        cout<<"Tea shop is closed"<<endl;
    }

    return 0;
}
