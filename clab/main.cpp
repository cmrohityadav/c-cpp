#include <iostream>
#include <thread>
#include <queue>
#include <vector>
#include <chrono>
#include <functional>
#include <mutex>
#include <condition_variable>

using namespace std;

class Executor {

private:
    queue<function<void()>> m_taskQueue;

    vector<thread> m_threads;

    mutex m_mutex;
    condition_variable m_cv;

    bool m_stop = false;

public:

    // Constructor
    Executor(int numberOfThreads) {

        for (int i = 0; i < numberOfThreads; i++) {

            m_threads.push_back(
                thread(&Executor::executeTask, this)
            );
        }
    }

      // Worker thread
    void executeTask() {

        while (true) {

            function<void()> func;

            {
                unique_lock<mutex> lock(m_mutex);

                // Wait until:
                // 1. task available ho
                // OR
                // 2. shutdown ho raha ho
                m_cv.wait(lock, [this]() {

                    return !m_taskQueue.empty() || m_stop;

                });


                // Agar shutdown ho gaya
                // aur queue bhi empty hai
                if (m_stop && m_taskQueue.empty()) {
                    return;
                }


                // Queue se task nikalo
                func = move(m_taskQueue.front());

                m_taskQueue.pop();
            }

            // IMPORTANT:
            // Mutex unlock hone ke baad task execute karo
            func();
        }
    }



    // Add task to queue
    void addTaskToQueue(function<void()> fn) {

        {
            lock_guard<mutex> lock(m_mutex);

            cout << "Adding function to queue" << endl;

            m_taskQueue.push(fn);
        }

        // Kisi ek waiting worker ko notify karo
        m_cv.notify_one();
    }


  
    // Shutdown
    void shutdown() {

        {
            lock_guard<mutex> lock(m_mutex);

            m_stop = true;
        }

        // Sab workers ko wake up karo
        m_cv.notify_all();


        // Workers ke finish hone ka wait karo
        for (auto& thread : m_threads) {

            if (thread.joinable()) {
                thread.join();
            }
        }
    }
};


int main() {

    // 4 worker threads
    Executor exe(4);


    // 20 tasks
    for (int i = 0; i < 20; i++) {

        exe.addTaskToQueue([i]() {

            cout << "Hello I am " << i
                 << " | Thread ID: "
                 << this_thread::get_id()
                 << endl;

            cout << "Processing..." << endl;

            this_thread::sleep_for(
                chrono::seconds(2)
            );

            cout << "Finished " << i << endl;
        });
    }


    // Shutdown
    exe.shutdown();

    return 0;
}