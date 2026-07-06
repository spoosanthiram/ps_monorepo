#include "algo/basic/min_heap.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("MinHeap Simple")
{
    ps::algo::MinHeap<int> heap;
    REQUIRE(heap.is_empty());

    using IntCompare = bool (*)(int, int);
    using IntIndex = void (*)(int, std::size_t);

    auto int_compare = [](int lhs, int rhs) -> bool { return lhs < rhs; };
    auto int_index = [](int element, std::size_t i) {};

    ps::algo::MinHeap<int, IntCompare, IntIndex> heap2{int_compare, int_index};
}
