#include <iostream>
#include <thread>
#include <mutex>
#include <map>
#include <chrono>

std::mutex orderBookMutex;
std::map<int, int> orderBook;

void updateOrderBook(int threadId, int price, int quantity) {
    std::unique_lock<std::mutex> ulvariable(orderBookMutex);

    std::cout << "Thread " << threadId << ": Lock acquired, updating order book...\n";

    // Critical section - protected access
    orderBook[price] += quantity;
    std::cout << "Thread " << threadId << ": Added quantity " << quantity << " at price " << price << "\n";

    // Temporary unlock for non-critical work (e.g., logging)
    ulvariable.unlock();
    std::cout << "Thread " << threadId << ": Unlocked temporarily for logging...\n";
    std::this_thread::sleep_for(std::chrono::seconds(10)); // simulate delay

    // Non-critical work done, now relock
    ulvariable.lock();
    std::cout << "Thread " << threadId << ": Relocked to finalize update...\n";

    // Final updates (e.g., audit)
    std::cout << "Thread " << threadId << ": Finalizing update.\n";
}

void printOrderBook() {
    std::unique_lock<std::mutex> lock(orderBookMutex);
    std::cout << "\nFinal Order Book:\n";
    for (const auto& entry : orderBook) {
        std::cout << "Price: " << entry.first << " => Quantity: " << entry.second << "\n";
    }
}

int main() {
    std::thread thread1(updateOrderBook, 1, 100, 10);
    std::thread thread2(updateOrderBook, 2, 101, 5);
    std::thread thread3(updateOrderBook, 3, 100, 15);

    thread1.join();
    thread2.join();
    thread3.join();

    printOrderBook();
    return 0;
}
