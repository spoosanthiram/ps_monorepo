#include <atomic>
#include <iostream>
#include <thread>

std::atomic_bool x;
std::atomic_bool y;

std::atomic_int z;

void write_x()
{
    x.store(true, std::memory_order_seq_cst);
}

void writex_y()
{
    y.store(true, std::memory_order_seq_cst);
}

void read_x_then_y()
{
    while (!x.load(std::memory_order_seq_cst)) {
        ;
    }
    if (y.load(std::memory_order_seq_cst)) {
        ++z;
    }
}

void read_y_then_x()
{
    while (!y.load(std::memory_order_seq_cst)) {
        ;
    }
    if (x.load(std::memory_order_seq_cst)) {
        ++z;
    }
}

int main()
{
    x = false;
    y = false;

    z = 0;

    std::thread t1{write_x};
    std::thread t2{writex_y};

    std::thread t3{read_x_then_y};
    std::thread t4{read_y_then_x};

    t1.join();
    t2.join();

    t3.join();
    t4.join();

    std::cout << "z: " << z << '\n';

    return 0;
}
