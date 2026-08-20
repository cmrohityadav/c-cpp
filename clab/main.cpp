#include<iostream>
#include<thread>
#include<mutex>
std::mutex mtx;
void worker(){

    std::unique_lock<std::mutex>lock(mtx);

    std::cout<<"Doing Critical Section..."<<std::endl;

    lock.unlock();

    std::cout << "Doing Non-critical work...\n";

    lock.lock();

    std::cout << "Doing Critical section again...\n";

}

int main(){

    std::thread t1(worker);

    t1.join();

    return 0;
}