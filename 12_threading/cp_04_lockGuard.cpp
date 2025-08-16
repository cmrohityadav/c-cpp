#include <iostream>
#include <thread>
#include<mutex>
int counter = 0;
std::mutex myMtxTaala; 
void increment() { 
    for (int i = 0; i < 1000000; ++i){ 
        std::lock_guard<std::mutex> myChowidar(myMtxTaala);
        counter++; 
        
    } 
} 

int main() { 
std::thread threadOne(increment); 
std::thread threadTwo(increment);

threadOne.join(); 
threadTwo.join(); 

std::cout << "Final counter: " << counter << std::endl; 

return 0; 

}