#include "sandbox/roblox/StrInt.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("StrInt Basic")
{
    Ps::Algo::StrInt zero{0};
    REQUIRE(zero.to_decimal_string() == "0");
    const auto zero_x_9 = zero * 9;
    REQUIRE(zero_x_9.to_decimal_string() == "0");

    Ps::Algo::StrInt x{1810};
    REQUIRE(x.to_decimal_string() == "1,810");
    const auto x2 = x * 2;
    REQUIRE(x2.to_decimal_string() == "3,620");

    REQUIRE(x < x2);
}
