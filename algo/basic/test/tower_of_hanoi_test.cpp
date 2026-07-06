#include "algo/basic/tower_of_hanoi.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("TowerOfHanoi BaseCase0")
{
    ps::algo::TowerOfHanoi toh{0};
    REQUIRE(toh.source().is_empty());
    REQUIRE(toh.intermediate().is_empty());
    REQUIRE(toh.destination().is_empty());
    toh.solve();
    REQUIRE(toh.source().is_empty());
    REQUIRE(toh.intermediate().is_empty());
    REQUIRE(toh.destination().is_empty());
}

TEST_CASE("TowerOfHanoi BaseCase1")
{
    ps::algo::TowerOfHanoi toh{1};
    REQUIRE(toh.source().size() == 1);
    REQUIRE(toh.intermediate().is_empty());
    REQUIRE(toh.destination().is_empty());
    toh.solve();
    REQUIRE(toh.source().is_empty());
    REQUIRE(toh.intermediate().is_empty());
    REQUIRE(toh.destination().size() == 1);
}
