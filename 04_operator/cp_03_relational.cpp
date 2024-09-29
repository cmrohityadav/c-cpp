#include<iostream>
using namespace std;
/*
==
>
>=
<
<=
!=


*/
int main()
{
    
    int iCups;
    cout<<"Enter the number of cups you have"<<endl;
    cin>>iCups;

    if(iCups>20){
        cout<<"You will get a Gold Badge"<<endl;
    }
    else if(iCups>=10 &&iCups<=20){
     cout<<"You will get a Silver Badge"<<endl;
    }else{
cout<<"No badge for you"<<endl;
    }

    return 0;
}
