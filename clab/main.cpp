#include <iostream>
#include <thread>
#include <vector>
#include <semaphore>
#include <chrono>

using namespace std::chrono_literals;


std::counting_semaphore<4> order_slots(2);

void process_order(int order_id)
{
    std::cout<< "[Order " << order_id << "] Waiting for processing slot...\n";

    // Wait until a slot becomes available
    order_slots.acquire();

    std::cout<< "[Order " << order_id << "] Processing started\n";

    // Simulate order validation + risk checks + processing
    std::this_thread::sleep_for(3s);

    std::cout<< "[Order " << order_id << "] Processing completed\n";

    // Return the slot for another order
    order_slots.release();
}

int main()
{
    std::vector<std::thread> workers;

    // Simulating incoming orders
    for (int order_id = 1; order_id <= 20; ++order_id)
    {
        workers.emplace_back(process_order, order_id);
    }

    // Wait for all orders to finish
    for (auto& worker : workers)
    {
        worker.join();
    }

    std::cout << "\nAll orders processed.\n";

    return 0;
}