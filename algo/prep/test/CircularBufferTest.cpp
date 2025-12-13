#include "algo/prep/CircularBuffer.h"

#include <catch2/catch_test_macros.hpp>

#include <iostream>

TEST_CASE("CircularBuffer Basic")
{
    Ps::Algo::CircularBuffer buf{4};
    buf.push_back(1);
    buf.push_back(2);
    buf.push_back(3);
    buf.print();
    buf.push_back(4);
    buf.print();
    buf.push_back(5);
    buf.print();
    std::cout << buf.pop_back() << '\n';
    buf.print();
    buf.push_back(6);
    buf.print();
}
