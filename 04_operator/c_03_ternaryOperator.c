#include<stdio.h>

int main(){

    int iNumber;
    printf("Enter Any Number : ");
    scanf("%d",&iNumber);

    iNumber%2==0?printf("Even Number"): printf("Odd Number");

    return 0;
}