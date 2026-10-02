#include "algo/basic/max_heap.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("MaxHeap Simple")
{
    ps::algo::MaxHeap<int> heap;
    REQUIRE(heap.is_empty());

    ps::algo::MaxHeap<int> heap2;
    heap2.push(12);
    REQUIRE(heap2.size() == 1);
    REQUIRE(heap2.top() == 12);
}

TEST_CASE("MaxHeap Build Max Heap")
{
    std::vector<int> elements{22, 15, 24, 1, 7, 23, 2, 29, 27, 10, 8, 13, 3, 18, 16};
    ps::algo::MaxHeap<int> heap{elements};
    REQUIRE(heap.top() == 29);
}

TEST_CASE("MaxHeap Push/Pop")
{
    std::vector<int> elements{22, 15, 24, 1, 7, 23, 2, 29, 27, 10, 8, 13, 3, 18, 16};
    ps::algo::MaxHeap<int> heap{elements};
    REQUIRE(heap.top() == 29);

    heap.push(4);
    REQUIRE(heap.size() == elements.size() + 1);
    REQUIRE(heap.top() == 29);
    heap.push(34);
    REQUIRE(heap.top() == 34);
    REQUIRE(heap.size() == elements.size() + 2);

    REQUIRE(heap.pop() == 34);
    REQUIRE(heap.size() == elements.size() + 1);
    REQUIRE(heap.top() == 29);
}
