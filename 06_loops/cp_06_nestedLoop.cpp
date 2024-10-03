// Write a program that brews multiple cups of different types of tea. For each type of tea, brew 3 cups using a nested loop.
#include<iostream>
using namespace std;

int main()
{
    string sTeaTypes[]={"ginger tea","orange tea","green tea","black tea","lemon tea"};
    
    for(int iCnt=0;iCnt<5;iCnt++){

        cout<<"brewing "<<sTeaTypes[iCnt]<<"..."<<endl;

        for(int iCnt2=1;iCnt2<=3;iCnt2++){
            cout<<"brewing "<<iCnt2<<" cup of "<<sTeaTypes[iCnt]<<endl;
        }
    }
    return 0;
}
