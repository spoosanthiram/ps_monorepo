#include "algo/basic/small_primes.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("SmallPrimes Simple")
{
    ps::algo::SmallPrimes sp;

    REQUIRE(sp.get_prime(0) == 2);
    REQUIRE(sp.get_prime(2) == 5);
    REQUIRE(sp.get_prime(5) == 13);
    REQUIRE(sp.get_prime(19) == 71);
    REQUIRE(sp.get_prime(99) == 541);
    REQUIRE(sp.get_prime(999) == 7919);
    REQUIRE(sp.get_prime(9999) == 104729);
}

TEST_CASE("Is Prime")
{
    REQUIRE_FALSE(ps::algo::is_prime(1));
    REQUIRE(ps::algo::is_prime(2));
    REQUIRE(ps::algo::is_prime(5));
    REQUIRE_FALSE(ps::algo::is_prime(8));
    REQUIRE(ps::algo::is_prime(23));
    REQUIRE_FALSE(ps::algo::is_prime(43050));
    REQUIRE(ps::algo::is_prime(43051));
    REQUIRE_FALSE(ps::algo::is_prime(64880));
    REQUIRE(ps::algo::is_prime(100043));
}
