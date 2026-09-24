#include <iostream>
#include <thread>
#include <functional>

void increamentWorker(int& i){
    i++;
}

void execute(void (*callback_func)(int&),int& i){

    callback_func(i);

}

int main()
{   
    int counter=10;

    execute(increamentWorker,counter);
    
    std::cout<<"counter: "<<counter<<std::endl;

    return 0;
}