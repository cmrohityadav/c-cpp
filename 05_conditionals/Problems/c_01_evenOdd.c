#include<stdio.h>

int main(){

    int iNum;
    printf("Enter the Number : ");
    scanf("%d",&iNum);
    if(iNum%2==0){
        printf("Even Number");
    }else{
        printf("Odd number");
    }

    return 0;
}