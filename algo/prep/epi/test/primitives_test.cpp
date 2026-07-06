#include "algo/prep/epi/primitives.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Primitives Parity")
{
    uint64_t x = 0xa31;
    REQUIRE(ps::algo::parity(x));
    REQUIRE(ps::algo::parity_using_lookup(x));

    x = 0xaaaaaaaaaa;
    REQUIRE_FALSE(ps::algo::parity(x));
    REQUIRE_FALSE(ps::algo::parity_using_lookup(x));
}

TEST_CASE("Primitives Swap Bits")
{
    uint64_t x = 0xb1ac; // 1011 0001 1010 1100
    //                              9        2
    uint64_t y = 0xb3a8; // 1011 0011 1010 1000
    REQUIRE(ps::algo::swap_bits(x, 9, 2) == y);

    REQUIRE(ps::algo::swap_bits(x, 2, 8) == x);
}

TEST_CASE("Primitives Reverse Bits")
{
    uint64_t x = 0xaaaaaaaaaaaaaaaa;
    uint64_t expected = 0x5555555555555555;
    REQUIRE(ps::algo::reverse_bits(x) == expected);
}

TEST_CASE("Primitives Closest Int With Same Bit Weight")
{
    uint64_t x = 7;
    uint64_t expected = 11;
    REQUIRE(ps::algo::closest_int_with_same_bit_weight(x) == expected);
}

TEST_CASE("Primitives Multiply With No Operator")
{
    REQUIRE(ps::algo::add_no_op(5, 5) == 10);
    REQUIRE(ps::algo::multiply_no_op(7, 8) == 56);
    REQUIRE(ps::algo::multiply_no_op(582, 357) == 207774);
}

TEST_CASE("Primitives Power")
{
    REQUIRE(ps::algo::power(53, 12) == 491258904256726154641.0);
}

TEST_CASE("Primitives Is Decimal Palindrome")
{
    REQUIRE(ps::algo::is_decimal_palindrome(0));
    REQUIRE_FALSE(ps::algo::is_decimal_palindrome(-76));
    REQUIRE(ps::algo::is_decimal_palindrome(7));
    REQUIRE_FALSE(ps::algo::is_decimal_palindrome(23));
    REQUIRE(ps::algo::is_decimal_palindrome(454));
    REQUIRE(ps::algo::is_decimal_palindrome(62577526));
    REQUIRE_FALSE(ps::algo::is_decimal_palindrome(87651));
}

TEST_CASE("Primitives Random")
{
    int a = 5;
    int b = 18;
    int result = ps::algo::random(a, b);
    REQUIRE(result >= a);
    REQUIRE(result <= b);
    result = ps::algo::random(a, b);
    REQUIRE(result >= a);
    REQUIRE(result <= b);
    result = ps::algo::random(a, b);
    REQUIRE(result >= a);
    REQUIRE(result <= b);
    result = ps::algo::random(a, b);
    REQUIRE(result >= a);
    REQUIRE(result <= b);
    result = ps::algo::random(a, b);
    REQUIRE(result >= a);
    REQUIRE(result <= b);

    a = 2;
    b = 18;
    result = ps::algo::random(a, b);
    REQUIRE(result >= a);
    REQUIRE(result <= b);
    result = ps::algo::random(a, b);
    REQUIRE(result >= a);
    REQUIRE(result <= b);

    a = 23424;
    b = 980643;
    result = ps::algo::random(a, b);
    REQUIRE(result >= a);
    REQUIRE(result <= b);
    result = ps::algo::random(a, b);
    REQUIRE(result >= a);
    REQUIRE(result <= b);
    result = ps::algo::random(a, b);
    REQUIRE(result >= a);
    REQUIRE(result <= b);
    result = ps::algo::random(a, b);
    REQUIRE(result >= a);
    REQUIRE(result <= b);
    result = ps::algo::random(a, b);
    REQUIRE(result >= a);
    REQUIRE(result <= b);
    result = ps::algo::random(a, b);
    REQUIRE(result >= a);
    REQUIRE(result <= b);
    result = ps::algo::random(a, b);
    REQUIRE(result >= a);
    REQUIRE(result <= b);
    result = ps::algo::random(a, b);
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
        ps::algo::Interval a{-2, 3};
        ps::algo::Interval b{4, 11};
        REQUIRE_FALSE(ps::algo::is_intersect(a, b));
    }
    {
        // -------
        // 2     5
        //       --------
        //       5      9
        ps::algo::Interval a{2, 5};
        ps::algo::Interval b{5, 9};
        REQUIRE(ps::algo::is_intersect(a, b));
    }
    {
        //  ----------
        // -12       -3
        //        ---------
        //       -5       -1
        ps::algo::Interval a{-12, -3};
        ps::algo::Interval b{-5, -1};
        REQUIRE(ps::algo::is_intersect(a, b));
    }
    {
        //  ----------
        // 23        67
        //        ----------
        //       25        180
        ps::algo::Interval a{23, 67};
        ps::algo::Interval b{25, 180};
        REQUIRE(ps::algo::is_intersect(a, b));
    }
    {
        //           ----------
        //          18        25
        //     ----------
        //    10        23
        ps::algo::Interval a{18, 25};
        ps::algo::Interval b{10, 23};
        REQUIRE(ps::algo::is_intersect(a, b));
    }
    {
        //           ----------
        //          18        25
        //  ---------
        // 10       18
        ps::algo::Interval a{18, 25};
        ps::algo::Interval b{10, 18};
        REQUIRE(ps::algo::is_intersect(a, b));
    }
    {
        //                 -----------
        //                354        456
        //   ----------
        // -100      294
        ps::algo::Interval a{354, 456};
        ps::algo::Interval b{-100, 294};
        REQUIRE_FALSE(ps::algo::is_intersect(a, b));
    }
}

TEST_CASE("Primitives Rectangle Intersection")
{
    ps::algo::Rectangle r1{1, 1, 1, 1};
    ps::algo::Rectangle r2{2, 2, 4, 4};
    ps::algo::Rectangle result_rect;
    auto retval = ps::algo::is_intersect(r1, r2, result_rect);
    REQUIRE(retval == true);
    ps::algo::Rectangle expected_rect{2, 2, 0, 0};
    REQUIRE(result_rect == expected_rect);
}
