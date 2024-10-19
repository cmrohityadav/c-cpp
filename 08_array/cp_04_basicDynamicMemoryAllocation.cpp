#include<iostream>
using namespace std;

int * pPrepareChaiOrders(int iCups){
    
    int * pOrders=new int [iCups];

    for(int i=0;i<iCups;i++){
        pOrders[i]=(i+1)*10;
    }

    return pOrders;

}
int main()
{
    int iCups=5;

    int * pOrder=pPrepareChaiOrders(iCups);

    for(int i=0;i<iCups;i++){
        cout<<"Cups : "<<i+1 <<" has "<< pOrder[i]<<" ml"<<endl;
    }

    delete [] pOrder;
    return 0;
}
