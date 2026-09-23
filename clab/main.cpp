#include <iostream>
#include <thread>
#include <semaphore>
#include <chrono>

using namespace std::chrono_literals;

std::binary_semaphore entry_token(0);

void organizer()
{
    std::cout << "[Organizer] Waiting for special entry...\n";

    std::this_thread::sleep_for(3s);

    std::cout << "[Organizer] Entry token issued!\n";

    // Token available
    entry_token.release();
}

void guest()
{
    std::cout << "[Guest] Waiting for entry token...\n";

    // Token nahi hai -> BLOCK
    entry_token.acquire();

    std::cout << "[Guest] Token received. Entering event...\n";
}

int main()
{
    std::thread t1(organizer);
    std::thread t2(guest);

    t1.join();
    t2.join();

    return 0;
}