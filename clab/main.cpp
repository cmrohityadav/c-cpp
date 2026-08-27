#include <iostream>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <chrono>

int sharedData = 0;

std::shared_mutex mtx;

void reader(int id)
{
    mtx.lock_shared();

    std::cout << "Reader " << id
              << " is reading: "
              << sharedData << "\n";

    std::this_thread::sleep_for(
        std::chrono::seconds(2)
    );

    mtx.unlock_shared();

    std::cout << "Reader " << id
              << " finished reading\n";
}

void writer(int id)
{
    mtx.lock();

    std::cout << "\nWriter " << id
              << " is writing...\n";

    sharedData++;

    std::this_thread::sleep_for(
        std::chrono::seconds(2)
    );

    std::cout << "Writer " << id
              << " updated value to: "
              << sharedData << "\n\n";

    mtx.unlock();
}

int main()
{
    std::thread r1(reader, 1);
    std::thread r2(reader, 2);
    std::thread w1(writer, 1);

    std::this_thread::sleep_for(std::chrono::seconds(10));
    
    std::thread w2(writer, 2);
    std::thread r3(reader, 3);
    std::thread r4(reader, 4);





    r1.join();
    r2.join();
    r3.join();
    w1.join();
    r4.join();
    w2.join();

    return 0;
}