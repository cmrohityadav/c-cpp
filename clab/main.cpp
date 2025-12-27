#include<iostream>
#include<thread>
#include<chrono>
#include<mutex>

int balance=100;
std::mutex mtx;
void Deposite(int amt){
    mtx.lock();
    
    int temp=balance;
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    temp=temp+amt;
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    balance=temp;

    mtx.unlock();
}

int main(){

    std::thread t1(Deposite,50);
    std::thread t2(Deposite,100);
    std::thread t3(Deposite,10);
    std::thread t4(Deposite,10);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    std::cout<<"Balance: "<<balance<<std::endl;

    return 0;
}