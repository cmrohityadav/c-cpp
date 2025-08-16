#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <chrono>

std::mutex myMutex;
std::queue<int> myQueue;
std::condition_variable mycv;

void txprod() {
    for (int count = 1; count <= 5; ++count) {
        std::this_thread::sleep_for(std::chrono::seconds(2));

        {
            std::lock_guard<std::mutex> lock(myMutex);
            myQueue.push(count);
            std::cout << "Produced: " << count << std::endl;
        }

        mycv.notify_one();
    }
}

void txcons() {
    while (true) {
        std::unique_lock<std::mutex> lock(myMutex);

        // Wait until queue is not empty
        mycv.wait(lock, []() { return !myQueue.empty(); });

        int countValue = myQueue.front();
        myQueue.pop();

        lock.unlock();  // optional, unlock before printing

        std::cout << "Consumed: " << countValue << std::endl;

        if (countValue == 5) break;  // stop after last item
    }
}

int main() {
    std::thread producerThread(txprod);
    std::thread consumerThread(txcons);

    producerThread.join();
    consumerThread.join();

    return 0;
}
