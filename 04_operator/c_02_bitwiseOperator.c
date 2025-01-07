#include<stdio.h>

int main(){

    int iOne=60;
    int iTwo=2;

    // Bit by AND &
    int iResult= iOne & iTwo;

    printf("Bit by AND  & : %d\n",iResult);
    

    // Bit by OR |
    iResult=iOne | iTwo;
    printf("Bit by OR |: %d\n",iResult);

    //Bitwise XOR ^
    iResult=iOne^iTwo;
    printf("Bitwise XOR ^: %d\n",iResult);

    //  Negation ~
    iResult=~iTwo;
    printf("Negation ~: %d\n",iResult);


    // Left Shift >>
    iResult=iTwo<<1;
    // iTwo *2^1
    //any number Multiplying by 2 raise to power by that left shift number

    printf("Left Shift >> %d\n",iResult);

  
    iResult=iTwo<<2;
    // iTwo *2^2

    printf("Left Shift >> %d\n",iResult);


    /*
    Right Shift >>

    resutNumber=anyNum/2^that right shift number

    here we are dividing any number by 2 raise to power  that number
    
    */

   int iThree=100;
   iResult=iThree>>1;

printf("Right Shift >> %d\n",iResult);

    return 0;
}