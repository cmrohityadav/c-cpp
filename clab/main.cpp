#include<iostream>
#include <thread>
#include <mutex>
int counter=0;
std::mutex m;
void inc(){
    for(int i=0;i<1000000;i++){
        std::lock_guard<std::mutex>lg(m);
        counter++;
    }
}

void dec(){
    for(int i=0;i<1000000;i++){
        std::lock_guard<std::mutex> lg(m);
        counter--;
    }
}
int main(){

    std::thread tInc(inc);

    std::thread tDec(dec);

    tDec.join();
    tInc.join();

    std::cout<<counter<<std::endl;

    return 0;
}