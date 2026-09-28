#include <chrono>
#include <future>
#include <iostream>

using namespace std::literals::chrono_literals;

int get_answer()
{
    std::this_thread::sleep_for(1s);
    return 23;
}

void do_other_stuff()
{
    std::this_thread::sleep_for(1s);
}

int main()
{
    // Async future
    {
        const auto t0 = std::chrono::system_clock::now();

        std::future<int> answer = std::async(std::launch::async, get_answer);
        do_other_stuff();
        std::cout << "Answer: " << answer.get() << '\n';

        const auto t1 = std::chrono::system_clock::now();
        std::cout << "Time for sync launch: " << std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0) << '\n';
    }

    // Deferred future
    {
        const auto t0 = std::chrono::system_clock::now();

        std::future<int> answer = std::async(std::launch::deferred, get_answer);
        do_other_stuff();
        std::cout << "Answer: " << answer.get() << '\n';

        const auto t1 = std::chrono::system_clock::now();
        std::cout << "Time for deferred launch: " << std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0)
                  << '\n';
    }

    return 0;
}
