#include "algo/basic/MinHeap.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("MinHeap Simple")
{
    Ps::Algo::MinHeap<int> heap;
    REQUIRE(heap.is_empty());

    using IntCompare = bool (*)(int, int);
    using IntIndex = void (*)(int, std::size_t);

    auto int_compare = [](int lhs, int rhs) -> bool { return lhs < rhs; };
    auto int_index = [](int element, std::size_t i) {};

    Ps::Algo::MinHeap<int, IntCompare, IntIndex> heap2{int_compare, int_index};
}
