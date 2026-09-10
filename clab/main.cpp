#include<iostream>
#include<thread>
#include<queue>
#include<vector>
#include<chrono>
#include <functional>
using namespace std;
std::queue<std::function<void()>> m_taskQueue;

void addTaskToQueue(std::function<void()>fn){
    std::cout<<"adding  function to queue "<<std::endl;
    m_taskQueue.push(fn);
}
class Executor{

    std::vector<std::thread>m_threads;
    public:
    Executor(){
        m_threads.push_back(std::thread(&Executor::executeTask,this));
    }

    void executeTask(){
        while(true){
            if(!m_taskQueue.empty()){
                const auto& func=m_taskQueue.front();
                func();
                m_taskQueue.pop();
            }
        }
    }

    void shutdown(){
        for(auto& thread:m_threads){
            if(thread.joinable()){
                thread.join();
            }
        }
    }

};


int main(){

    Executor exe;

    addTaskToQueue([](){
        std::cout<<"Hello I am from main, Thread id: "<<std::this_thread::get_id()<<std::endl;
    });

    exe.shutdown();

    return 0;
}