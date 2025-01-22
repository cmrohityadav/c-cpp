#include<stdio.h>
/*
It may give error
*/
int main(){

    register int iNum=10;

    int *a=&iNum;
    printf("%d",*a);
    return 0;
}