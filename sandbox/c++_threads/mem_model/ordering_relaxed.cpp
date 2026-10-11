#include <atomic>
#include <iostream>
#include <thread>

std::atomic_bool x;
std::atomic_bool y;

std::atomic_int z;

void write_x_then_y()
{
    x.store(true, std::memory_order_relaxed);
    y.store(true, std::memory_order_relaxed);
}

void read_y_then_x()
{
    while (!y.load(std::memory_order_relaxed)) {
        ;
    }
    if (x.load(std::memory_order_relaxed)) {
        ++z;
    }
}

int main()
{
    x = false;
    y = false;

    z = 0;

    std::thread t1{write_x_then_y};
    std::thread t2{read_y_then_x};

    t1.join();
    t2.join();

    std::cout << "z: " << z << '\n';

    return 0;
}
