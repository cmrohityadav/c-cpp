#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::mutex m1;
std::mutex m2;

void thread1() {
    m1.lock();

    std::cout << "Thread 1 locked m1\n";

    // Thread 2 ko m2 lock karne ka chance diya
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout << "Thread 1 waiting for m2\n";

    m2.lock();  // yahan wait karega

    std::cout << "Thread 1 working\n";

    m2.unlock();
    m1.unlock();
}

void thread2() {
    m2.lock();

    std::cout << "Thread 2 locked m2\n";

    // Thread 1 ko m1 lock karne ka chance diya
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout << "Thread 2 waiting for m1\n";

    m1.lock();  // yahan wait karega

    std::cout << "Thread 2 working\n";

    m1.unlock();
    m2.unlock();
}

int main() {
    std::thread threadOneObject(thread1);
    std::thread threadTwoObject(thread2);

    threadOneObject.join();
    threadTwoObject.join();

    return 0;
}