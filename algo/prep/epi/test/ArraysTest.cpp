#include "algo/prep/epi/Arrays.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Arrays India Flag Partition")
{
    // pivot value of 0, pivot_index = 0
    {
        std::vector<int> nums{0, 1, 2, 0, 2, 1, 1};
        Ps::Algo::india_flag_partition(nums, 0);
        REQUIRE(nums == std::vector<int>{0, 0, 2, 2, 1, 1, 1});
    }

    // pivot value of 1, pivot_index = 5
    {
        std::vector<int> nums{0, 1, 2, 0, 2, 1, 1};
        Ps::Algo::india_flag_partition(nums, 5);
        REQUIRE(nums == std::vector<int>{0, 0, 1, 1, 1, 2, 2});
    }

    // pivot value of 2, pivot_index = 2
    {
        std::vector<int> nums{0, 1, 2, 0, 2, 1, 1};
        Ps::Algo::india_flag_partition(nums, 2);
        REQUIRE(nums == std::vector<int>{0, 1, 0, 1, 1, 2, 2});
    }
}

TEST_CASE("Arrays Increment Arbitrary Precision Int")
{
    REQUIRE(Ps::Algo::increment(std::vector<int>{}) == std::vector<int>{});
    REQUIRE(Ps::Algo::increment(std::vector<int>{1, 2, 9}) == std::vector<int>{1, 3, 0});
    REQUIRE(Ps::Algo::increment(std::vector<int>{9, 9, 9, 9}) == std::vector<int>{1, 0, 0, 0, 0});
}

TEST_CASE("Arrays Multiply Two Arbitrary Precision Ints")
{
    const auto x = std::vector<int>{2, 3, 7};
    const auto y = std::vector<int>{4};
    REQUIRE(Ps::Algo::multiply(x, y) == std::vector<int>{9, 4, 8});

    const auto x2 = std::vector<int>{1, 9, 3, 7, 0, 7, 7, 2, 1};
    const auto y2 = std::vector<int>{-7, 6, 1, 8, 3, 8, 2, 5, 7, 2, 8, 7};
    REQUIRE(Ps::Algo::multiply(x2, y2) ==
            std::vector<int>{-1, 4, 7, 5, 7, 3, 9, 5, 2, 5, 8, 9, 6, 7, 6, 4, 1, 2, 9, 2, 7});
}

TEST_CASE("Arrays Can Reach End")
{
    std::vector<int> a{3, 3, 1, 0, 2, 0, 1};
    REQUIRE(Ps::Algo::can_reach_end(a));

    std::vector<int> b{3, 2, 0, 0, 2, 0, 1};
    REQUIRE_FALSE(Ps::Algo::can_reach_end(b));
}

TEST_CASE("Arrays Remove Duplicate")
{
    // empty array
    {
        std::vector<int> numbers;
        const auto valid_nums = Ps::Algo::remove_dup(numbers);
        REQUIRE(valid_nums == 0);
        REQUIRE(numbers == std::vector<int>{});
    }

    // one element array
    {
        std::vector<int> numbers{23};
        const auto valid_nums = Ps::Algo::remove_dup(numbers);
        REQUIRE(valid_nums == 1);
        REQUIRE(numbers == std::vector<int>{23});
    }

    // normal case, sorted numbers with duplicate
    {
        std::vector<int> numbers{2, 3, 5, 5, 9, 10, 10, 18, 18, 18, 23, 25};
        const auto valid_nums = Ps::Algo::remove_dup(numbers);
        REQUIRE(valid_nums == 8);
        REQUIRE(numbers == std::vector<int>{2, 3, 5, 9, 10, 18, 23, 25, 18, 18, 23, 25});
    }
}

TEST_CASE("Arrays Buy And Sell Stock Once")
{
    std::vector<double> prices{310.0, 315.0, 275.0, 295.0, 260.0, 270.0, 290.0, 230.0, 255.0, 250.0};
    REQUIRE(Ps::Algo::buy_and_sell_stock_once(prices) == 30.0);
}

TEST_CASE("Arrays Generate Primes")
{
    {
        const auto primes = Ps::Algo::generate_primes(0);
        REQUIRE(primes == std::vector<uint32_t>{});
    }
    {
        const auto primes = Ps::Algo::generate_primes(1);
        REQUIRE(primes == std::vector<uint32_t>{});
    }
    {
        const auto primes = Ps::Algo::generate_primes(2);
        REQUIRE(primes == std::vector<uint32_t>{2});
    }
    {
        const auto primes = Ps::Algo::generate_primes(23);
        REQUIRE(primes == std::vector<uint32_t>{2, 3, 5, 7, 11, 13, 17, 19, 23});
    }
    {
        const auto primes = Ps::Algo::generate_primes(100);
        REQUIRE(primes == std::vector<uint32_t>{2,  3,  5,  7,  11, 13, 17, 19, 23, 29, 31, 37, 41,
                                                43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97});
    }
    {
        const auto primes = Ps::Algo::generate_primes(16777215);
        CHECK(primes[99] == 541);
        CHECK(primes[499] == 3571);
        CHECK(primes[875] == 6803);
        CHECK(primes[4999] == 48611);
        CHECK(primes[9999] == 104729);
        CHECK(primes[99999] == 1299709);
        CHECK(primes[500000] == 7368791);
        CHECK(primes[1000000] == 15485867);
    }
}

TEST_CASE("Arrays Apply Permutation")
{
    std::vector<char> a{'a', 'b', 'c', 'd'};
    std::vector<int> perm{2, 0, 1, 3};
    Ps::Algo::apply_permutation(a, perm);
    REQUIRE(a == std::vector<char>{'b', 'c', 'a', 'd'});
}

TEST_CASE("Arrays Next Permutation")
{
    std::vector<int> perm{6, 2, 1, 5, 4, 3, 0};
    REQUIRE(Ps::Algo::next_permutation(perm) == std::vector<int>{6, 2, 3, 0, 1, 4, 5});

    std::vector<int> perm2{0, 1, 4, 3, 2};
    REQUIRE(Ps::Algo::next_permutation(perm2) == std::vector<int>{0, 2, 1, 3, 4});

    std::vector<int> perm3{1, 0, 3, 2};
    REQUIRE(Ps::Algo::next_permutation(perm3) == std::vector<int>{1, 2, 0, 3});

    std::vector<int> perm4{3, 2, 1, 0};
    REQUIRE(Ps::Algo::next_permutation(perm4) == std::vector<int>{});
}

TEST_CASE("Arrays Sudoku Check")
{
    std::vector<std::vector<uint32_t>> sudoku;
    sudoku.push_back(std::vector<uint32_t>{5, 6, 1, 8, 4, 7, 9, 2, 3});
    sudoku.push_back(std::vector<uint32_t>{3, 7, 9, 5, 2, 1, 6, 8, 4});
    sudoku.push_back(std::vector<uint32_t>{4, 2, 8, 9, 6, 3, 1, 7, 5});
    sudoku.push_back(std::vector<uint32_t>{6, 1, 3, 7, 8, 9, 5, 4, 2});
    sudoku.push_back(std::vector<uint32_t>{7, 9, 4, 6, 5, 2, 3, 1, 8});
    sudoku.push_back(std::vector<uint32_t>{8, 5, 2, 1, 3, 4, 7, 9, 6});
    sudoku.push_back(std::vector<uint32_t>{9, 3, 5, 4, 7, 8, 2, 6, 1});
    sudoku.push_back(std::vector<uint32_t>{1, 4, 6, 2, 9, 5, 8, 3, 7});
    sudoku.push_back(std::vector<uint32_t>{2, 8, 7, 3, 1, 6, 4, 5, 9});

    REQUIRE(Ps::Algo::is_valid_sudoku(sudoku));

    sudoku[3][5] = 1;
    REQUIRE_FALSE(Ps::Algo::is_valid_sudoku(sudoku));
}

TEST_CASE("Arrays Pascal Triangle")
{
    const auto pt = Ps::Algo::pascal_triangle(5);
    REQUIRE(pt[0] == std::vector<int>{1});
    REQUIRE(pt[1] == std::vector<int>{1, 1});
    REQUIRE(pt[2] == std::vector<int>{1, 2, 1});
    REQUIRE(pt[3] == std::vector<int>{1, 3, 3, 1});
    REQUIRE(pt[4] == std::vector<int>{1, 4, 6, 4, 1});
    REQUIRE(pt[5] == std::vector<int>{1, 5, 10, 10, 5, 1});
}
