#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using std::cout;

std::recursive_timed_mutex mtx;

void hello(int i, int threadId)
{
    cout << "Thread " << threadId
         << " -> Trying to get lock...\n";

    if (mtx.try_lock_for(std::chrono::seconds(3)))
    {
        cout << "Thread " << threadId
             << " -> 🔒 Lock acquired | Hello : " << i << '\n';

        // Same thread recursively locking the same mutex
        if (i < 5)
        {
            hello(i + 1, threadId);
        }

        // Just to make Thread 2 wait and show timed behaviour
        if (i == 1)
        {
            std::this_thread::sleep_for(std::chrono::seconds(5));
        }

        mtx.unlock();

        cout << "Thread " << threadId
             << " -> 🔓 Lock released\n";
    }
    else
    {
        cout << "Thread " << threadId
             << " -> ⏰ Timeout! Could not get lock\n";
    }
}

int main()
{
    std::thread t1(hello, 1, 1);

    // Give Thread 1 a small head start
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    std::thread t2(hello, 1, 2);
    std::thread t3(hello, 1, 3);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}