#include<iostream>
#include<thread>
#include<future>
#include<chrono>


void worker(std::promise<int>p){

    std::cout<<"Getting Result....\n";
    std::this_thread::sleep_for(std::chrono::seconds(5));

    std::cout<<"Calculating....\n";

    std::this_thread::sleep_for(std::chrono::seconds(3));
    // Worker thread result provide karta hai
    p.set_value(100);


}

int main(){

    std::promise<int>int_promise;
    
    // Promise aur future ko connect karo
    std::future<int>int_future=int_promise.get_future();

    std::thread thread_worker(worker,std::move(int_promise));

    int int_result=int_future.get();

    std::cout<<"Result: "<<int_result<<std::endl;

    if(thread_worker.joinable()){
        thread_worker.join();
    }

    return 0;
}