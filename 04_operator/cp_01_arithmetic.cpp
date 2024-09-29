#include<iostream>
using namespace std;
/*

/:: division
*:: multiply
-:: sub
+::add
%:: module

*/
int main()
{
    int iCups;
    double dPricePerCup,dTotalPrice,dDiscountedPrice;

    cout<<"enter the number of tea cups\n";
    cin>>iCups;
    cout<<"Enter the price per cup\n";
    cin>>dPricePerCup;

    dTotalPrice=iCups*dPricePerCup;

    // apply 5% discount if total price is above 100;

    if(dTotalPrice>100){
        dDiscountedPrice=dTotalPrice-(dTotalPrice*(0.05));
        cout<<"Discounted price is: "<<dDiscountedPrice<<endl;

    }else{
            cout<<"Total price is "<<dTotalPrice<<endl;
    }


    return 0;
}
