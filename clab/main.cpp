#include<iostream>
#include<thread>
#include<chrono>
#include<stop_token>

using namespace std::chrono_literals;

void shutdown_msg(){
    std::cout<<"This Apllication going to stop... ... ..."<<std::endl;
}

void worker(std::stop_token token,int id){
    
    int count=0;

    while(!token.stop_requested()){

        std::cout << "Working: " << ++count << '\n';

        std::this_thread::sleep_for(200ms);
    }

    std::cout << "Worker " << id << " stopped\n";
}

int main(){

    std::stop_source source;

    std::stop_token token=source.get_token();

    std::stop_callback callbackObject(token,[](){
        shutdown_msg();
    });

    std::jthread t1(worker,token,1);
    std::jthread t2(worker,token,2);

    std::this_thread::sleep_for(1s);

    source.request_stop();

    t1.join();
    t2.join();

    std::cout << "Application shutdown complete\n";

    return 0;
}