#include "sandbox/roblox/Int.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Int Basic")
{
    Ps::Algo::Int zero{0};
    REQUIRE(zero.to_hex_str() == "00000000");
    Ps::Algo::Int one{1};
    REQUIRE(zero < one);

    Ps::Algo::Int x1{210};
    Ps::Algo::Int x2{918};
    REQUIRE(x1 + x2 == Ps::Algo::Int{1128});
}
