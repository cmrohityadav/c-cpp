#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <chrono>

std::mutex myMutex;
std::queue<int> myQueue;
std::condition_variable mycv;

void producer() {
    int count = 1;
    while (count <= 5) {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        {
            std::lock_guard<std::mutex> lock(myMutex);
            myQueue.push(count);
            std::cout << "[Producer] Produced: " << count << std::endl;
        }

        count++;

        // Notify ALL consumers
        mycv.notify_all();
    }
}

void consumer(int id) {
    while (true) {
        int value = -1;
        {
            std::unique_lock<std::mutex> lock(myMutex);
            mycv.wait(lock, []() { return !myQueue.empty(); });

            value = myQueue.front();
            myQueue.pop();

            std::cout << "[Consumer " << id << "] Consumed: " << value << std::endl;
        }

        if (value == 5) break; // Exit when last item consumed
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

int main() {
    std::thread producerThread(producer);

    std::thread consumerThread1(consumer, 1);
    std::thread consumerThread2(consumer, 2);
    std::thread consumerThread3(consumer, 3);

    producerThread.join();
    consumerThread1.join();
    consumerThread2.join();
    consumerThread3.join();

    std::cout << "All threads completed." << std::endl;
    return 0;
}
