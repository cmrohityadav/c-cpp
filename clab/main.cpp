#include<iostream>
#include<thread>
#include<chrono>

void function1(){
    std::cout<<"Hello from Function1"<<std::endl;
    
    std::this_thread::sleep_for(std::chrono::seconds(5));

    std::cout << "Function1 finished" << std::endl;
}

void function2(){
    std::cout<<"Hello from Function2"<<std::endl;
}
void function3(){
    std::cout<<"Hello from Function3"<<std::endl;
}
int main(){

    std::thread t1(function1);
    std::cout<<"Thread t1 created"<<std::endl;

    std::thread t2(function2);
    std::cout<<"Thread t2 created"<<std::endl;

    t1.join(); //WAIT POINT
    std::cout<<"Join t1"<<std::endl;

    std::thread t3(function3);
    std::cout<<"Thread t3 created"<<std::endl;
    t3.join();
    std::cout<<"Join t3"<<std::endl;


    t2.join();
    std::cout<<"Join t2"<<std::endl;


    return 0;
}