#include<iostream>
#include<thread>
#include<mutex>
using  std::cout;

std::recursive_mutex mtx;
void hello(int i){
    mtx.lock();
    cout<<" Hello : "<<i<<std::endl;
    hello(++i);

    mtx.unlock();
}
int main(){

    
    return 0;
}