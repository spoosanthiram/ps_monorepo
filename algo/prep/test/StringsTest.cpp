#include "algo/prep/Strings.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Strings Palindrome")
{
    REQUIRE(Ps::Algo::is_palindrome(""));
    REQUIRE(Ps::Algo::is_palindrome("p"));
    REQUIRE(Ps::Algo::is_palindrome("madam"));
}

TEST_CASE("Strings RemoveReplace")
{
    // {a, c, d, b, b, c, a} -> {d, d, c, d, c, d, d}
    std::array<char, 7> str1{'a', 'c', 'd', 'b', 'b', 'c', 'a'};
    std::array<char, 7> expected1{'d', 'd', 'c', 'd', 'c', 'd', 'd'};
    const auto size1 = Ps::Algo::remove_replace(str1.data(), str1.size());
    REQUIRE(size1 == 7);
    REQUIRE(str1 == expected1);
}

TEST_CASE("Convert Numbers to Words")
{
    uint64_t x = 0;
    REQUIRE(Ps::Algo::convert_to_words(x) == "zero");

    x = 1;
    REQUIRE(Ps::Algo::convert_to_words(x) == "one");

    x = 7;
    REQUIRE(Ps::Algo::convert_to_words(x) == "seven");

    x = 10;
    REQUIRE(Ps::Algo::convert_to_words(x) == "ten");

    x = 18;
    REQUIRE(Ps::Algo::convert_to_words(x) == "eighteen");

    x = 23;
    REQUIRE(Ps::Algo::convert_to_words(x) == "twenty three");

    x = 60;
    REQUIRE(Ps::Algo::convert_to_words(x) == "sixty");

    x = 100;
    REQUIRE(Ps::Algo::convert_to_words(x) == "one hundred");

    x = 210;
    REQUIRE(Ps::Algo::convert_to_words(x) == "two hundred ten");

    x = 723;
    REQUIRE(Ps::Algo::convert_to_words(x) == "seven hundred twenty three");

    x = 825;
    REQUIRE(Ps::Algo::convert_to_words(x) == "eight hundred twenty five");

    x = 918;
    REQUIRE(Ps::Algo::convert_to_words(x) == "nine hundred eighteen");
}

TEST_CASE("Convert Numbers to Words Big")
{
    uint64_t x = 1'000;
    REQUIRE(Ps::Algo::convert_to_words(x) == "one thousand");

    x = 1'977;
    REQUIRE(Ps::Algo::convert_to_words(x) == "one thousand nine hundred seventy seven");

    x = 2'013;
    REQUIRE(Ps::Algo::convert_to_words(x) == "two thousand thirteen");

    x = 1'000'000;
    REQUIRE(Ps::Algo::convert_to_words(x) == "one million");

    x = 4'256'935;
    REQUIRE(Ps::Algo::convert_to_words(x) == "four million two hundred fifty six thousand nine hundred thirty five");

    x = 87'162'543'956;
    REQUIRE(
        Ps::Algo::convert_to_words(x) ==
        "eighty seven billion one hundred sixty two million five hundred fourty three thousand nine hundred fifty six");

    x = 33'091'844'110'815; // US national debt at this time of writing this code
    REQUIRE(Ps::Algo::convert_to_words(x) ==
            "thirty three trillion ninety one billion eight hundred fourty four million one hundred ten thousand eight "
            "hundred fifteen");

    x = 10'000'000'000'000'000;
    REQUIRE(Ps::Algo::convert_to_words(x) == "ten quadrillion");
}
