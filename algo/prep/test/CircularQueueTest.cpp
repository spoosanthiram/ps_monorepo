#include "algo/prep/CircularQueue.h"

#include <catch2/catch_test_macros.hpp>

#include <iostream>
#include <thread>

TEST_CASE("CircularQueue Basic")
{
    Ps::Algo::CircularQueue q{5};
    q.enqueue(3);
    q.enqueue(5);
    q.enqueue(1);
    REQUIRE(q.size() == 3);

    REQUIRE(q.dequeue() == 3);
    REQUIRE(q.size() == 2);
    q.enqueue(10);
    q.enqueue(18);
    q.enqueue(23);
    REQUIRE(q.size() == 5);
}

namespace {

Ps::Algo::CircularQueue circular_queue{5};

void producer()
{
    int n = 10;
    while (n > 0) {
        circular_queue.enqueue(n);
        --n;
    }
}

void consumer()
{
    int n = 10;
    while (n-- > 0) {
        std::cout << circular_queue.dequeue() << '\n';
    }
}

} // namespace

TEST_CASE("CircularQueue ProducerConsumer")
{
    std::thread t1{consumer};
    std::thread t2{producer};

    t1.join();
    t2.join();
}
