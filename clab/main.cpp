#include <iostream>
#include <thread>
#include <functional>

void increamentWorker(int& i){
    i++;
}

int main()
{   
    int counter=1;
    std::thread t(increamentWorker,std::ref(counter));

    if(t.joinable()){
        t.join();
    }

    std::cout<<"counter: "<<counter<<std::endl;

    return 0;
}