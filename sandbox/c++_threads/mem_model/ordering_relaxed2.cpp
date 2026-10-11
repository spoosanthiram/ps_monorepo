#include <atomic>
#include <format>
#include <iostream>
#include <thread>

std::atomic_int x{0};
std::atomic_int y{0};
std::atomic_int z{0};

std::atomic_bool go{false};

constexpr auto loop_count = 10;

struct ReadValues
{
    int x;
    int y;
    int z;
};

ReadValues values1[loop_count];
ReadValues values2[loop_count];
ReadValues values3[loop_count];
ReadValues values4[loop_count];
ReadValues values5[loop_count];

void increment(std::atomic_int* a, ReadValues* values)
{
    while (!go) {
        std::this_thread::yield();
    }

    for (auto i = 0; i < loop_count; ++i) {
        values[i].x = x.load(std::memory_order_relaxed);
        values[i].y = y.load(std::memory_order_relaxed);
        values[i].z = z.load(std::memory_order_relaxed);

        a->store(i + 1, std::memory_order_relaxed);

        std::this_thread::yield();
    }
}

void read_values(ReadValues* values)
{
    while (!go) {
        std::this_thread::yield();
    }

    for (auto i = 0; i < loop_count; ++i) {
        values[i].x = x.load(std::memory_order_relaxed);
        values[i].y = y.load(std::memory_order_relaxed);
        values[i].z = z.load(std::memory_order_relaxed);

        std::this_thread::yield();
    }
}

void print_values(ReadValues* values)
{
    for (auto i = 0; i < loop_count; ++i) {
        if (i > 0) {
            std::cout << ", ";
        }
        std::cout << std::format("[{}, {}, {}]", values[i].x, values[i].y, values[i].z);
    }
    std::cout << '\n';
}

int main()
{
    {
        std::jthread t1{increment, &x, values1};
        std::jthread t2{increment, &y, values2};
        std::jthread t3{increment, &z, values3};

        std::jthread t4{read_values, values4};
        std::jthread t5{read_values, values5};

        go = true;
    }

    print_values(values1);
    print_values(values2);
    print_values(values3);
    print_values(values4);
    print_values(values5);

    return 0;
}
