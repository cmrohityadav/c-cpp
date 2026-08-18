#include<iostream>
#include <thread>
void printCounter(){
    for(int i=0;i<10;i++){
        std::cout<<i<<std::endl;
    }
}
int main(){

    std::thread t1(printCounter);

    t1.join(); //Current thread wait karega jab tak t1 wala thread finish nahi ho jata
    std::thread t2(printCounter);

    if(t2.joinable()){ //Ye check karta hai ki std::thread object ke paas currently ek active/joinable thread association hai ya nahi.
        t2.join();
    }

    


    return 0;
}