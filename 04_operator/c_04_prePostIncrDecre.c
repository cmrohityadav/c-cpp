#include<stdio.h>

int main(){
//POST INCREAMENT
    int a=10;
    int iOne=a++;
    // first it assign it's original value to iOne
    //then it will increase
    printf("Value of iOne : %d and a :%d\n",iOne,a);



//PRE INCREAMENT

    int b=10;
    int iTwo=++b;

 printf("Value of iTwo : %d and b :%d\n",iTwo,b);



 //DECREAMENT


//  PRE 
  int c=100;
  int preDec=--c;
 printf("Value of preDec : %d and c :%d\n",preDec,c);
  
// POST

int d=999;
  int postDec=d--;
 printf("Value of postDec : %d and d :%d\n",postDec,d);
  

    return 0;
}