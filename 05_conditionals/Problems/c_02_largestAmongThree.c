#include<stdio.h>

int main(){

    int iOne,iTwo,iThree;
    printf("Enter all 3 number :");
    scanf("%d %d %d",&iOne,&iTwo,&iThree);

    if(iOne>iTwo && iOne>iThree){
        printf("%d is the largest",iOne);
    }else if(iTwo>iOne && iTwo>iThree){
        printf("%d is the largest",iTwo);
    }else{
        printf("%d is the largest",iThree);
    }
    

    return 0;
}