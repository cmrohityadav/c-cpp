#include<iostream>
using namespace std;
int main(){

    char p[]="rohit";

    char* const name=p;
    cout<<name<<endl;

    name[0]='P';

    cout<<name<<endl;

    // p = other; // Error


}