#include<iostream>
#include<thread>
#include<chrono>
#include<stop_token>

using namespace std::chrono_literals;

void worker(std::stop_token token){
    
    int count=0;

    while(!token.stop_requested()){

        std::cout << "Working: " << ++count << '\n';

        std::this_thread::sleep_for(200ms);
    }

    std::cout << "Worker stopping gracefully\n";
}

int main(){

    std::jthread t(worker);

    std::this_thread::sleep_for(1s);

    t.request_stop();

    return 0;
}