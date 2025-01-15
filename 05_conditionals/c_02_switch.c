#include<stdio.h>

int main(){

    printf("Enter 1 for EQ and 2  for FO");
    short iOption;
    scanf("%d",&iOption);

    switch(iOption){

        case 1:{
            printf("Its Equity Market");
            break;
        }
        case 2:{
            printf("Its Future and Option Market");
            break;
        }
        default:{
            printf("Invalid market selection");
        }
    }
    return 0;
}