#include<iostream>
using namespace std;

void pourChai(int iCups){

    iCups+=5;
    cout<<"Poured cups: "<<iCups<<endl;
}
int main()
{
    int iChaiCups=2;
    pourChai(iChaiCups);

    cout<<"Total cups are "<<iChaiCups<<endl;
    return 0;
}
