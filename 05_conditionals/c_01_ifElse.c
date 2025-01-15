#include<stdio.h>

int main(){

    int iAge;
    printf("Enter your age :");
    scanf("%d",&iAge);

    if(iAge<18){
        printf("you are teen");
    }else{
        printf("you are adult");
    }

    return 0;

}