#include<iostream>
#include<thread>
void  taskUploadFile(){
    std::cout<<"File Uploading...."<<std::endl;
    std::cout<<"File uploaded"<<std::endl;
}

void printGreet(std::string greet){ 
    std::cout << "thread function [printGreet] start" << std::endl; 
    std::cout << "Hello " << greet << std::endl; 
    std::cout << "thread function [printGreet] end" << std::endl; 
}

void backgroundTask(){ 
    std::cout << "background Task function thread started" << std::endl; 
    std::this_thread::sleep_for(std::chrono::seconds(5)); 
    std::cout << "background task done" << std::endl; 
    std::cout << "background Task function thread end" << std::endl; 
}
int main(){
    std::cout << "Main function start" << std::endl;

    std::thread worker1(taskUploadFile);

    worker1.detach();

    std::cout<<"Now in main function using detach it will not wait for it"<<std::endl;

    std::thread threadOne(printGreet, "Good Afternoon");

    threadOne.join(); 
    std::cout << "thread finished come back to main thread" << std::endl; 

    std::thread bgtask(backgroundTask); 
    bgtask.detach(); 
    std::cout << "sleeping main thread for 6 seconds" << std::endl; 
    std::this_thread::sleep_for(std::chrono::seconds(6)); 
    std::cout << "Main function end" << std::endl;

    return 0;
}