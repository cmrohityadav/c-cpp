#include<iostream>
using namespace std;

int iTotalChaiServerd(int placeholder[],int iSize){
 int iTotal=0;
 for(int i=0;i<iSize;i++){
    iTotal=iTotal+placeholder[i];
 }

 return iTotal;
}
int main()
{
    
    int iChaiServed[7]={50,60,90,10,100,150,45};

    int iTotal=iTotalChaiServerd(iChaiServed,7);
    cout<<"Total Served : "<<iTotal<<endl;
    
        return 0;
}
