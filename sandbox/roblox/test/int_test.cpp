#include "sandbox/roblox/int.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Int Basic")
{
    ps::algo::Int zero{0};
    REQUIRE(zero.to_hex_str() == "00000000");
    ps::algo::Int one{1};
    REQUIRE(zero < one);

    ps::algo::Int x1{210};
    ps::algo::Int x2{918};
    REQUIRE(x1 + x2 == ps::algo::Int{1128});
}
