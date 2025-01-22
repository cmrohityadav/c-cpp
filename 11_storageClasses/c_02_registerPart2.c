#include<stdio.h>
/*
It may give error
*/
int main(){

   int i=10;
   register int *a=&i;
   printf("%d",*a);
    return 0;
}