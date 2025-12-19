#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

using namespace std::literals::chrono_literals;

std::queue<int> data_queue;
std::mutex data_mutex;
std::condition_variable data_cv;

std::atomic_bool running = true;

void data_pub()
{
    static int data = 0;
    while (running) {
        {
            std::scoped_lock lck{data_mutex};
            data_queue.push(data);
        }
        data_cv.notify_one();
        ++data;
    }
}

void data_sub()
{
    while (running) {
        std::unique_lock lck{data_mutex};
        data_cv.wait(lck, []() { return !data_queue.empty(); });
        const auto data = data_queue.front();
        data_queue.pop();
        lck.unlock();
        std::cout << "data: " << data << '\n';
    }
}

int main()
{
    std::thread sub_thread{data_sub};
    std::thread pub_thread{data_pub};

    std::this_thread::sleep_for(5ms);
    running = false;

    pub_thread.join();
    sub_thread.join();

    return 0;
}
