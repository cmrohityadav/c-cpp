#include<iostream>
using namespace std;
/*
Write a program that skips brewing green tea if the user dislikes it. Use a continue statement to skip over green tea but brew other types of tea in a list.
*/
int main()
{
    string sTeaTypes[]={"ginger tea","orange tea","green tea","black tea","lemon tea"};

    for(int counter=0;counter<5;counter++){

        if(sTeaTypes[counter]=="green tea"){
            cout<<"skipping the "<<sTeaTypes[counter]<<endl;
            continue;
        }
        cout<<"Brewing "<<sTeaTypes[counter]<<"..."<<endl;

    }

    return 0;
}
