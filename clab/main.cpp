#include<iostream>
#include<thread>
#include<mutex>

int counter=0;
std::mutex m_mutex;


void worker(){

    if(m_mutex.try_lock()){
        std::cout << "Thread got the lock\n";
        std::cout<<std::this_thread::get_id()<<std::endl;
        counter++;


    }else{
         std::cout << "Thread could not get the lock\n";
    }

}
int main(){

    std::thread t(worker);
    std::thread t2(worker);

    t.join();
    t2.join();

    std::cout<<"Counter: "<<counter<<std::endl;
    return 0;
}