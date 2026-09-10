#include <iostream>
#include <future>
#include<thread>
#include<chrono>
int calculate()
{ 
    std::cout<<"Heavy calculation....\n";
    std::this_thread::sleep_for(std::chrono::seconds(5));
    return 100;
}

int main()
{
    std::future<int> result =
        std::async(std::launch::async, calculate);

    std::cout << "Main thread kuch aur kaam kar raha hai...\n";

    int value = result.get();

    std::cout << "Result = " << value << '\n';
}