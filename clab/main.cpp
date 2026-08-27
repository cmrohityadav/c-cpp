#include <iostream>
#include <thread>
#include <shared_mutex>
#include <chrono>

std::shared_timed_mutex mtx;

int sharedData = 100;

void reader(int id)
{
    std::cout << "Reader " << id
              << " -> Trying to get shared lock...\n";

    if (mtx.try_lock_shared_for(
            std::chrono::seconds(10)))
    {
        std::cout << "Reader " << id
                  << " -> Shared lock acquired\n";

        std::cout << "Reader " << id
                  << " -> Reading value: "
                  << sharedData << "\n";

        std::this_thread::sleep_for(
            std::chrono::seconds(2)
        );

        mtx.unlock_shared();

        std::cout << "Reader " << id
                  << " -> Shared lock released:Unlock\n";
    }
    else
    {
        std::cout << "Reader " << id
                  << " -> Timeout! Could not get shared lock\n";
    }
}

void writer(int id)
{
    std::cout << "Writer " << id
              << " -> Trying to get exclusive lock...\n";

    if (mtx.try_lock_for(
            std::chrono::seconds(3)))
    {
        std::cout << "Writer " << id
                  << " -> Exclusive lock acquired\n";

        sharedData += 10;

        std::this_thread::sleep_for(
            std::chrono::seconds(5)
        );

        std::cout << "Writer " << id
                  << " -> Updated value: "
                  << sharedData << "\n";

        mtx.unlock();

        std::cout << "Writer " << id
                  << " -> Exclusive lock released\n";
    }
    else
    {
        std::cout << "Writer " << id
                  << " -> Timeout! Could not get exclusive lock\n";
    }
}

int main()
{
    std::thread w1(writer, 1);
    std::thread r1(reader, 1);
    std::this_thread::sleep_for(
        std::chrono::milliseconds(100)
    );
    std::thread w2(writer, 2);

    std::thread r2(reader, 2);

    w1.join();
    w2.join();
    r1.join();
    r2.join();

    return 0;
}