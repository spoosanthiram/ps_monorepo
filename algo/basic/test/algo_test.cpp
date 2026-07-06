#include "algo/basic/algo.h"
#include "utils/utils.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("LeapYear")
{
    REQUIRE_FALSE(ps::algo::is_leap_year(1799));
    REQUIRE_FALSE(ps::algo::is_leap_year(1800));
    REQUIRE(ps::algo::is_leap_year(2000));
    REQUIRE(ps::algo::is_leap_year(2012));
    REQUIRE_FALSE(ps::algo::is_leap_year(2013));
    REQUIRE_FALSE(ps::algo::is_leap_year(2014));
    REQUIRE_FALSE(ps::algo::is_leap_year(2100));
}

TEST_CASE("Fibonacci")
{
    REQUIRE(ps::algo::fibonacci(0) == 0);
    REQUIRE(ps::algo::fibonacci(1) == 1);
    REQUIRE(ps::algo::fibonacci(5) == 5);
    REQUIRE(ps::algo::fibonacci(12) == 144);
    REQUIRE(ps::algo::fibonacci(20) == 6'765);
    REQUIRE(ps::algo::fibonacci(27) == 196'418);
    REQUIRE(ps::algo::fibonacci(60) == 1'548'008'755'920L);
}

TEST_CASE("IsPalindrome")
{
    REQUIRE(ps::algo::is_palindrome(0));
    REQUIRE_FALSE(ps::algo::is_palindrome(-76));
    REQUIRE(ps::algo::is_palindrome(7));
    REQUIRE_FALSE(ps::algo::is_palindrome(23));
    REQUIRE(ps::algo::is_palindrome(454));
    REQUIRE(ps::algo::is_palindrome(62577526));
    REQUIRE_FALSE(ps::algo::is_palindrome(87651));
}

TEST_CASE("Linear Search")
{
    std::vector<int> numbers{4, 9, 1, 8, 7, 3, 2, 5, 6};
    REQUIRE(ps::algo::linear_search(numbers, 7) == 4);
    REQUIRE(ps::algo::linear_search(numbers, 89) == -1);
}

TEST_CASE("Binary Search")
{
    std::vector<int> numbers{2, 9, 17, 34, 56, 234, 564, 789, 900, 1092};
    REQUIRE(ps::algo::binary_search(numbers, 564) == 6);
}

TEST_CASE("Maximum Subarray")
{
    std::vector<int> numbers{13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
    int64_t istart = 0;
    int64_t iend = 0;
    auto sum = ps::algo::maximum_subarray(numbers, istart, iend);
    REQUIRE(istart == 7);
    REQUIRE(iend == 10);
    REQUIRE(sum == 43);

    std::vector<int> numbers2{-2, 1, -3, 4, -1, 2, 1, -5, 4};
    sum = ps::algo::maximum_subarray(numbers2, istart, iend);
    REQUIRE(sum == 6);
    REQUIRE(istart == 3);
    REQUIRE(iend == 6);
}

TEST_CASE("Selection")
{
    std::vector<int> numbers{3, 2, 9, 0, 7, 5, 4, 8, 6, 1};
    REQUIRE(ps::algo::select(numbers, 7) == 7);
}

TEST_CASE("Inversions")
{
    std::vector<int> integers{1, 3, 5, 2, 4, 6};
    const auto inv = ps::algo::inversions(integers);
    REQUIRE(inv == 3);
}

TEST_CASE("AlgoClass Inversions")
{
    auto integers = ps::utils::read_integers("algo/basic/test/data/AlgoClassInversionsInput.txt");
    const auto inv = ps::algo::inversions(integers);
    REQUIRE(inv == 2'407'905'288);
}
