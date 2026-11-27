#include <atomic>
#include <thread>
#include <iostream>
#include <chrono>

struct Counters
{
    std::atomic<long long> a{0};
    std::atomic<long long> b{0};
};

int main()
{
    Counters c;

    auto start = std::chrono::steady_clock::now();

    std::thread t1([&] {
        for (int i = 0; i < 20'000'000; ++i)
            c.a.fetch_add(1, std::memory_order_relaxed);
    });

    std::thread t2([&] {
        for (int i = 0; i < 20'000'000; ++i)
            c.b.fetch_add(1, std::memory_order_relaxed);
    });

    t1.join();
    t2.join();

    auto end = std::chrono::steady_clock::now();

    std::cout << "A: " << c.a << '\n';
    std::cout << "B: " << c.b << '\n';

    std::cout << "Time: "
        << std::chrono::duration_cast<std::chrono::milliseconds>(
            end - start
        ).count()
        << " ms\n";
}