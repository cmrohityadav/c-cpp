#include<stdio.h>

int main(){


    int iStockPrice=150;
    printf("Stock Price at 9 AM : %d : \n",iStockPrice);

    iStockPrice=iStockPrice+2;
    printf("Stock Price at 9:15 AM  : %d : \n",iStockPrice);
// Alternative
    iStockPrice+=2;
    printf("Stock Price at 3.30 PM  : %d : \n",iStockPrice);


    return 0;
}