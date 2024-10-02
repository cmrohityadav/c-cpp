#include<iostream>
#include<string>
using namespace std;
/*

Create a program that asks the user if they want more tea. Keep asking them until they type "no" (case-insensitive), using a do-while loop.
*/
int main()
{   
    string sResponse;

   do{
    cout<<"Do you want more tea (yes/no) : ";
    getline(cin,sResponse);


   }while(sResponse!="no");
    
    
    return 0;
}
