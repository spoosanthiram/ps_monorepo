#include "algo/prep/others.h"

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

    auto actual = ps::algo::permutations("abc");
    std::sort(actual.begin(), actual.end());

    REQUIRE(actual == expected);
}

TEST_CASE("Skyline Problem")
{
    // example 1
    {
        std::vector<ps::algo::Building> buildings;
        buildings.push_back(ps::algo::Building{2, 9, 10});
        buildings.push_back(ps::algo::Building{3, 7, 15});
        buildings.push_back(ps::algo::Building{5, 12, 12});
        buildings.push_back(ps::algo::Building{15, 20, 10});
        buildings.push_back(ps::algo::Building{19, 24, 8});

        REQUIRE(ps::algo::skyline_area(buildings) == 212);
    }

    // example 2
    {
        std::vector<ps::algo::Building> buildings;
        buildings.push_back(ps::algo::Building{0, 2, 3});
        buildings.push_back(ps::algo::Building{2, 5, 3});

        REQUIRE(ps::algo::skyline_area(buildings) == 15);
    }
}
