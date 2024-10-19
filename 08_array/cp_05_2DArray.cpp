#include<iostream>
using namespace std;

int main()
{
    int iChaiSales[3][7]={
        {1,2,3,4,5,6,7},
        {10,20,30,40,50,60,70},
        {7,8,6,5,4,2,8}
    };


    for(int iRow=0;iRow<3;iRow++){

        cout<<"I am at Shop "<<iRow+1<<" : \n";
        

        for(int iCol=0;iCol<7;iCol++){

            cout<<iChaiSales[iRow][iCol]<<" Cups ";
        }
        cout<<endl;  
    }

    return 0;
}
