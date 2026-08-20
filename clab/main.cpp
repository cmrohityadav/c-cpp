#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>

std::queue<int> orders;

std::mutex m;
std::condition_variable cv;


// 🛵 Delivery Boy = Consumer
void deliveryBoy(int id) {

    while (true) {

        // Mutex lock
        std::unique_lock<std::mutex> lock(m);

        // Agar order nahi hai → mutex unlock + sleep
        // Order aane par → wake + mutex dobara lock
        cv.wait(lock, []() {
            return !orders.empty();
        });

        // Order queue se nikalo
        int order = orders.front();
        orders.pop();

        std::cout
            << "Delivery Boy "
            << id
            << " picked Order "
            << order
            << std::endl;

        // Mutex manually unlock
        // Kyunki ab queue ka kaam khatam
        lock.unlock();


        // 🚴 Delivery kar raha hai
        std::this_thread::sleep_for(
            std::chrono::seconds(2)
        );

        std::cout
            << "Delivery Boy "
            << id
            << " delivered Order "
            << order
            << std::endl;
    }
}


// 🛒 New Order = Producer
void createOrder(int orderId) {

    {
        // Queue ko lock karo
        std::lock_guard<std::mutex> lock(m);

        // New order queue mein daalo
        orders.push(orderId);

        std::cout
            << "New Order Created: "
            << orderId
            << std::endl;
    }

    // Kisi ek waiting delivery boy ko jagao
    cv.notify_one();
    
}


int main() {

    // 3 Delivery Boys
    std::thread boy1(deliveryBoy, 1);
    std::thread boy2(deliveryBoy, 2);
    std::thread boy3(deliveryBoy, 3);


    // Thoda wait taaki delivery boys wait state mein chale jayein
    std::this_thread::sleep_for(
        std::chrono::seconds(1)
    );


    // 🛒 Orders create ho rahe hain
    createOrder(101);

    std::this_thread::sleep_for(
        std::chrono::milliseconds(500)
    );

    createOrder(102);

    std::this_thread::sleep_for(
        std::chrono::milliseconds(500)
    );

    createOrder(103);


    // Threads ko wait karo
    boy1.join();
    boy2.join();
    boy3.join();

    return 0;
}