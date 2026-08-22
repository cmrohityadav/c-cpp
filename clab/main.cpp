#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::mutex m;

void greedyThread() {
    for (int i = 0; i < 1000000; i++) {
        m.lock();

        // Resource use kar raha hai
        std::cout << "Greedy thread working\n";

        m.unlock();

        // Turant dobara lock lene ki try
    }
}

void starvingThread() {
    std::cout << "Starving thread waiting for lock...\n";

    m.lock();

    std::cout << "Finally! Starving thread got the lock\n";

    m.unlock();
}

int main() {
    std::thread t1(greedyThread);
    std::thread t2(starvingThread);

    t1.join();
    t2.join();
}