#include <iostream>
#include <thread>
int counter = 0; 
void increment() { 
    for (int i = 0; i < 1000000; ++i){ 
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