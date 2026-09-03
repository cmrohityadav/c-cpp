#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
std::mutex mtx_for_result;
std::condition_variable result_notification;

struct Result
{
    char name[20];
    int score;
    int roll;
};

std::queue<Result> result_queue;
bool isReadyResult = false;
Result results[7] = {
    {"rohit", 80, 1},
    {"rahul", 70, 2},
    {"piyush", 80, 3},
    {"kaushal", 90, 4},
    {"manjit", 80, 5},
    {"anjali", 70, 6},
    {"roshani", 80, 7},
};

void teacher()
{
    int i = 0;
    while (i < 7)
    {

        std::unique_lock<std::mutex> lock(mtx_for_result);
        result_queue.push(results[i]);
        isReadyResult = true;

        mtx_for_result.unlock();

        result_notification.notify_one();
        i++;
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}

void live_result()
{
    std::cout << "live Result of coder\n";
    while (1)
    {
        std::unique_lock<std::mutex> lock(mtx_for_result);

        result_notification.wait(lock, [](){ return isReadyResult; });

        Result temp_result = result_queue.front();
        isReadyResult = false;
        result_queue.pop();
        lock.unlock();

        std::cout << "Student Name: " << temp_result.name << "Mark: " << temp_result.score << "Roll No.: " << temp_result.roll << std::endl;

        if (temp_result.score > 50)
        {
            std::cout << "Status: Pass\n";
        }
        else
        {
            std::cout << "Status: Fail\n";
        }
    }
}
int main()
{

    std::thread t1(teacher);
    std::thread t2(live_result);

    t1.join();
    t2.join();

    return 0;
}