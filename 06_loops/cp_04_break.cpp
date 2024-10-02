#include<iostream>
using namespace std;
/*
Write a program that keeps serving tea until the user says they’ve had enough (input 'stop'). Use a break statement to exit the loop when the user types 'stop'.
*/

int main()
{
    char cResponse;

    while(true){
        cout<<"Do you want more tea (\" e\" to exit)"<<endl;
        cin>>cResponse;
        if(cResponse=='e'){
            break;
        }
        cout<<"Here is your another cup of tea"<<endl;
    }
    cout<<"No more tea will be served to you"<<endl;
    return 0;
}
