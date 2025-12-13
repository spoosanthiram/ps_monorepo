#include "algo/prep/Recursion.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Permutations")
{
    std::vector<std::string> expected;
    expected.push_back("abc");
    expected.push_back("bac");
    expected.push_back("bca");
    expected.push_back("acb");
    expected.push_back("cab");
    expected.push_back("cba");
    std::sort(expected.begin(), expected.end());

    auto actual = Ps::Algo::permutations("abc");
    std::sort(actual.begin(), actual.end());

    REQUIRE(actual == expected);
}
