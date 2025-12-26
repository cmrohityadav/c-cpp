#include<iostream>
#include<thread>
#include<chrono>

void quantumCalculation(int a, int b){
    int msec=0;
    while(msec<100){
        std::cout<<"Calculating Quantum Addition...."<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        msec++;
    }

    std::cout<<"Final calculation: "<<a+b<<std::endl;
}

void quantumCalculationMul(int a, int b){
    int msec=0;
    while(msec<500){
        std::cout<<"Calculating Quantum Multiply...."<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        msec++;
    }

    std::cout<<"Final calculation Multiply: "<<a*b<<std::endl;
}
int main(){

    std::thread t1(quantumCalculation,10,10);
    std::thread t2(quantumCalculationMul,50,10);

    t1.join();
    t2.join();



    return 0;
}