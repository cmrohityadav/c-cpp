#include<iostream>
using namespace std;

int main()
{
    
   auto  preparedChai=[](int iCups){
        cout<<"preparing "<<iCups<<" cups of tea"<<endl;

    };

    preparedChai(4);

    return 0;
}
