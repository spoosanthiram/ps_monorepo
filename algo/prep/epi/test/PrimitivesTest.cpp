#include "algo/prep/epi/Primitives.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Primitives Parity")
{
    uint64_t x = 0xa31;
    REQUIRE(Ps::Algo::parity(x));
    REQUIRE(Ps::Algo::parity_using_lookup(x));

    x = 0xaaaaaaaaaa;
    REQUIRE_FALSE(Ps::Algo::parity(x));
    REQUIRE_FALSE(Ps::Algo::parity_using_lookup(x));
}

TEST_CASE("Primitives Swap Bits")
{
    uint64_t x = 0xb1ac; // 1011 0001 1010 1100
    //                              9        2
    uint64_t y = 0xb3a8; // 1011 0011 1010 1000
    REQUIRE(Ps::Algo::swap_bits(x, 9, 2) == y);

    REQUIRE(Ps::Algo::swap_bits(x, 2, 8) == x);
}

TEST_CASE("Primitives Reverse Bits")
{
    uint64_t x = 0xaaaaaaaaaaaaaaaa;
    uint64_t expected = 0x5555555555555555;
    REQUIRE(Ps::Algo::reverse_bits(x) == expected);
}

TEST_CASE("Primitives Closest Int With Same Bit Weight")
{
    uint64_t x = 7;
    uint64_t expected = 11;
    REQUIRE(Ps::Algo::closest_int_with_same_bit_weight(x) == expected);
}

TEST_CASE("Primitives Multiply With No Operator")
{
    REQUIRE(Ps::Algo::add_no_op(5, 5) == 10);
    REQUIRE(Ps::Algo::multiply_no_op(7, 8) == 56);
    REQUIRE(Ps::Algo::multiply_no_op(582, 357) == 207774);
}

TEST_CASE("Primitives Power")
{
    REQUIRE(Ps::Algo::power(53, 12) == 491258904256726154641.0);
}

TEST_CASE("Primitives Is Decimal Palindrome")
{
    REQUIRE(Ps::Algo::is_decimal_palindrome(0));
    REQUIRE_FALSE(Ps::Algo::is_decimal_palindrome(-76));
    REQUIRE(Ps::Algo::is_decimal_palindrome(7));
    REQUIRE_FALSE(Ps::Algo::is_decimal_palindrome(23));
    REQUIRE(Ps::Algo::is_decimal_palindrome(454));
    REQUIRE(Ps::Algo::is_decimal_palindrome(62577526));
    REQUIRE_FALSE(Ps::Algo::is_decimal_palindrome(87651));
}

TEST_CASE("Primitives Random")
{
    int a = 5;
    int b = 18;
    int result = Ps::Algo::random(a, b);
    REQUIRE(result >= a);
    REQUIRE(result <= b);
    result = Ps::Algo::random(a, b);
    REQUIRE(result >= a);
    REQUIRE(result <= b);
    result = Ps::Algo::random(a, b);
    REQUIRE(result >= a);
    REQUIRE(result <= b);
    result = Ps::Algo::random(a, b);
    REQUIRE(result >= a);
    REQUIRE(result <= b);
    result = Ps::Algo::random(a, b);
    REQUIRE(result >= a);
    REQUIRE(result <= b);

    a = 2;
    b = 18;
    result = Ps::Algo::random(a, b);
    REQUIRE(result >= a);
    REQUIRE(result <= b);
    result = Ps::Algo::random(a, b);
    REQUIRE(result >= a);
    REQUIRE(result <= b);

    a = 23424;
    b = 980643;
    result = Ps::Algo::random(a, b);
    REQUIRE(result >= a);
    REQUIRE(result <= b);
    result = Ps::Algo::random(a, b);
    REQUIRE(result >= a);
    REQUIRE(result <= b);
    result = Ps::Algo::random(a, b);
    REQUIRE(result >= a);
    REQUIRE(result <= b);
    result = Ps::Algo::random(a, b);
    REQUIRE(result >= a);
    REQUIRE(result <= b);
    result = Ps::Algo::random(a, b);
    REQUIRE(result >= a);
    REQUIRE(result <= b);
    result = Ps::Algo::random(a, b);
    REQUIRE(result >= a);
    REQUIRE(result <= b);
    result = Ps::Algo::random(a, b);
    REQUIRE(result >= a);
    REQUIRE(result <= b);
    result = Ps::Algo::random(a, b);
    REQUIRE(result >= a);
    REQUIRE(result <= b);
}

TEST_CASE("Primitives Interval Intersection")
{
    {
        //  -------
        // -2      3
        //            ---------
        //            4       11
        Ps::Algo::Interval a{-2, 3};
        Ps::Algo::Interval b{4, 11};
        REQUIRE_FALSE(Ps::Algo::is_intersect(a, b));
    }
    {
        // -------
        // 2     5
        //       --------
        //       5      9
        Ps::Algo::Interval a{2, 5};
        Ps::Algo::Interval b{5, 9};
        REQUIRE(Ps::Algo::is_intersect(a, b));
    }
    {
        //  ----------
        // -12       -3
        //        ---------
        //       -5       -1
        Ps::Algo::Interval a{-12, -3};
        Ps::Algo::Interval b{-5, -1};
        REQUIRE(Ps::Algo::is_intersect(a, b));
    }
    {
        //  ----------
        // 23        67
        //        ----------
        //       25        180
        Ps::Algo::Interval a{23, 67};
        Ps::Algo::Interval b{25, 180};
        REQUIRE(Ps::Algo::is_intersect(a, b));
    }
    {
        //           ----------
        //          18        25
        //     ----------
        //    10        23
        Ps::Algo::Interval a{18, 25};
        Ps::Algo::Interval b{10, 23};
        REQUIRE(Ps::Algo::is_intersect(a, b));
    }
    {
        //           ----------
        //          18        25
        //  ---------
        // 10       18
        Ps::Algo::Interval a{18, 25};
        Ps::Algo::Interval b{10, 18};
        REQUIRE(Ps::Algo::is_intersect(a, b));
    }
    {
        //                 -----------
        //                354        456
        //   ----------
        // -100      294
        Ps::Algo::Interval a{354, 456};
        Ps::Algo::Interval b{-100, 294};
        REQUIRE_FALSE(Ps::Algo::is_intersect(a, b));
    }
}

TEST_CASE("Primitives Rectangle Intersection")
{
    Ps::Algo::Rectangle r1{1, 1, 1, 1};
    Ps::Algo::Rectangle r2{2, 2, 4, 4};
    Ps::Algo::Rectangle result_rect;
    auto retval = Ps::Algo::is_intersect(r1, r2, result_rect);
    REQUIRE(retval == true);
    Ps::Algo::Rectangle expected_rect{2, 2, 0, 0};
    REQUIRE(result_rect == expected_rect);
}
