#include<iostream>
using namespace std;
/*
    A tea shop offers discounts based on the number of tea cups ordered. Write a program that checks the number of cups ordered and applies a discount:* More than 20 cups: 20% discount
Between 10 and 20 cups: 10% discount
Less than 10 cups: No discount
*/
int main()
{
        cout<<"Welcome To Tea Shop"<<endl;

        int iTeaPricePerCup=10;
        int iNumberOfCups;
        float fDiscountedPrice;

        cout<<"Enter the Number of Cups"<<endl;
        cin>>iNumberOfCups;

        if(iNumberOfCups>20){
            fDiscountedPrice=iNumberOfCups*iTeaPricePerCup-(iNumberOfCups*iTeaPricePerCup)*0.2;
            cout<<"Discounted Price :"<<fDiscountedPrice<<endl;
        }else if(iNumberOfCups<10){
            fDiscountedPrice=iNumberOfCups*iTeaPricePerCup;
            cout<<"Total price is :"<<fDiscountedPrice<<endl;
        }else{
            fDiscountedPrice=iNumberOfCups*iTeaPricePerCup-(iNumberOfCups*iTeaPricePerCup)*0.1;
            cout<<"Discounted Price :"<<fDiscountedPrice<<endl; 
        }
        

    return 0;
}
