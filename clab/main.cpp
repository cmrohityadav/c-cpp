#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::mutex m1;
std::mutex m2;

void thread1() {
    while (true) {
        m1.lock();

        std::cout << "Thread 1 got m1\n";

        // Dusra mutex try karo
        if (m2.try_lock()) {
            std::cout << "Thread 1 got m2\n";
            std::cout << "Thread 1 working\n";

            m2.unlock();
            m1.unlock();

            break;
        }
        else {
            std::cout << "Thread 1: m2 busy, releasing m1\n";

            m1.unlock();

            std::this_thread::sleep_for(
                std::chrono::milliseconds(100)
            );
        }
    }
}

void thread2() {
    while (true) {
        m2.lock();

        std::cout << "Thread 2 got m2\n";

        // Dusra mutex try karo
        if (m1.try_lock()) {
            std::cout << "Thread 2 got m1\n";
            std::cout << "Thread 2 working\n";

            m1.unlock();
            m2.unlock();

            break;
        }
        else {
            std::cout << "Thread 2: m1 busy, releasing m2\n";

            m2.unlock();

            std::this_thread::sleep_for(
                std::chrono::milliseconds(100)
            );
        }
    }
}

int main() {
    std::thread t1(thread1);
    std::thread t2(thread2);

    t1.join();
    t2.join();
}