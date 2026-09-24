#include <iostream>
#include <thread>

int main()
{
    unsigned int count = std::thread::hardware_concurrency();

    std::cout << "Hardware concurrency: "<< count << '\n';
}