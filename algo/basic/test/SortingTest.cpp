#include "algo/basic/Sorting.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Sorting Insersion Sort")
{
    std::vector<int> a{3, 5, 7, 2, 9, 6, 8, 5, 1};
    Ps::Algo::insertion_sort(a);
    std::vector<int> expected{1, 2, 3, 5, 5, 6, 7, 8, 9};
    CHECK(a == expected);
}

TEST_CASE("Sorting Merge Sort")
{
    std::vector<int> a{5, 4, 10, 6, 13, 9, 1, 11, 9, 14, 12, 3, 0, 2, 7};
    Ps::Algo::merge_sort(a);
    std::vector<int> expected{0, 1, 2, 3, 4, 5, 6, 7, 9, 9, 10, 11, 12, 13, 14};
    CHECK(a == expected);
}

TEST_CASE("Sorting Quick Sort")
{
    std::vector<int> a{5, 1, 6, 3, 7, 2, 8, 4};
    Ps::Algo::quick_sort(a);
    std::vector<int> expected{1, 2, 3, 4, 5, 6, 7, 8};
    CHECK(a == expected);
}

TEST_CASE("Sorting Randomized Quick Sort")
{
    std::vector<int> a{5, 1, 6, 3, 7, 2, 8, 4};
    Ps::Algo::randomized_quick_sort(a);
    std::vector<int> expected{1, 2, 3, 4, 5, 6, 7, 8};
    CHECK(a == expected);
}
