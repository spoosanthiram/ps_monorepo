#include "algo/basic/String.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("String to Integer")
{
    REQUIRE(Ps::Algo::stoi("142", 10) == 142);
    REQUIRE(Ps::Algo::stoi("-3453", 10) == -3453);
    REQUIRE(Ps::Algo::stoi("10101100", 2) == 0xac);
    REQUIRE(Ps::Algo::stoi("aa", 16) == 170);
    REQUIRE(Ps::Algo::stoi("3a7b9e", 16) == 0x3a7b9e);
}

TEST_CASE("Integer to String")
{
    REQUIRE(Ps::Algo::to_string(322089, 10) == "322089");
    REQUIRE(Ps::Algo::to_string(0xd86a, 2) == "1101100001101010");
    REQUIRE(Ps::Algo::to_string(13, 4) == "31");
}
