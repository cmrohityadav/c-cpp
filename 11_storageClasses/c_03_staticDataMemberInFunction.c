#include<stdio.h>

int countFun(){
int count=0;

return ++count;

}
/*
On the first call:

static int count = 0; initializes count to 0.
++count increments it to 1.
The function returns 1.
On subsequent calls:

count is not reinitialized (because it’s static).
++count increments its current value.
The updated value is returned.
*/
int countStaticFunc(){
//using static count variable is created in data section not in call stack
    static int count=0;
    return ++count;
}
int main(){

    printf("%d \n",countFun());
    printf("%d \n",countFun());
    printf("%d \n",countFun());
    printf("%d \n",countFun());

    printf("\n");

    printf("%d \n",countStaticFunc());
    printf("%d \n",countStaticFunc());
    printf("%d \n",countStaticFunc());


    return 0;
}