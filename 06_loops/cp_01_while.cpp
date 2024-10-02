/*
    Write a program that keeps track of tea orders. Each time a cup of tea is made, decrease the number of cups remaining. The loop should run until all cups are served.

*/
#include<iostream>
using namespace std;

int main()
{
    int iTeaCups;
    cout<<"Enter the number of tea cups"<<endl;
    cin>>iTeaCups;

    while(iTeaCups>0){
        cout<<"Serving a cup of tea\n "<<iTeaCups<<" remaining"<<endl;
        iTeaCups--;

    }
    cout<<"All tea cups are served."<<endl;


    return 0;
}
