#include<iostream>
#include<thread>
#include<mutex>
#include<chrono>
using  std::cout;

std::timed_mutex mtx;

void task(int id){

    if(mtx.try_lock_for(std::chrono::seconds(15))){ //max. 15 sec tak wait karega lock lene k liye

        cout<<"Thread "<<id<<" got the lock\n";

        std::this_thread::sleep_for(std::chrono::seconds(3));

        cout<<"Thread "<<id<<"  unlocking....\n";

        mtx.unlock();


    }else{
       std::cout << "Thread " << id << " timeout!\n";
    }
}

int main(){

    std::thread t1(task,1);
    std::thread t2(task,2);
    std::thread t3(task,3);
    std::thread t4(task,4);
    std::thread t5(task,5);
    std::thread t6(task,6);
    std::thread t7(task,7);
    std::thread t8(task,8);
    
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    t8.join();

    return 0;
}