#include "algo/prep/epi/strings.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Strings Palindrome")
{
    REQUIRE(ps::algo::is_palindrome(""));
    REQUIRE(ps::algo::is_palindrome("p"));
    REQUIRE(ps::algo::is_palindrome("madam"));
}

TEST_CASE("String to Integer")
{
    REQUIRE(ps::algo::stoi("142", 10) == 142);
    REQUIRE(ps::algo::stoi("-3453", 10) == -3453);
    REQUIRE(ps::algo::stoi("10101100", 2) == 0xac);
    REQUIRE(ps::algo::stoi("aa", 16) == 170);
    REQUIRE(ps::algo::stoi("3a7b9e", 16) == 0x3a7b9e);
}

TEST_CASE("Integer to String")
{
    REQUIRE(ps::algo::to_string(322089, 10) == "322089");
    REQUIRE(ps::algo::to_string(0xd86a, 2) == "1101100001101010");
    REQUIRE(ps::algo::to_string(13, 4) == "31");
}

TEST_CASE("Strings RemoveReplace")
{
    // {a, c, d, b, b, c, a} -> {d, d, c, d, c, d, d}
    std::array<char, 7> str1{'a', 'c', 'd', 'b', 'b', 'c', 'a'};
    std::array<char, 7> expected1{'d', 'd', 'c', 'd', 'c', 'd', 'd'};
    const auto size1 = ps::algo::remove_replace(str1.data(), str1.size());
    REQUIRE(size1 == 7);
    REQUIRE(str1 == expected1);
}

TEST_CASE("Convert Numbers to Words")
{
    REQUIRE(ps::algo::convert_to_words(0) == "zero");
    REQUIRE(ps::algo::convert_to_words(1) == "one");
    REQUIRE(ps::algo::convert_to_words(7) == "seven");

    REQUIRE(ps::algo::convert_to_words(10) == "ten");
    REQUIRE(ps::algo::convert_to_words(18) == "eighteen");
    REQUIRE(ps::algo::convert_to_words(23) == "twenty three");
    REQUIRE(ps::algo::convert_to_words(60) == "sixty");

    REQUIRE(ps::algo::convert_to_words(100) == "one hundred");
    REQUIRE(ps::algo::convert_to_words(210) == "two hundred ten");
    REQUIRE(ps::algo::convert_to_words(723) == "seven hundred twenty three");
    REQUIRE(ps::algo::convert_to_words(825) == "eight hundred twenty five");
    REQUIRE(ps::algo::convert_to_words(901) == "nine hundred one");
    REQUIRE(ps::algo::convert_to_words(999) == "nine hundred ninety nine");
}

TEST_CASE("Convert Numbers to Words Big")
{
    REQUIRE(ps::algo::convert_to_words(1'000) == "one thousand");
    REQUIRE(ps::algo::convert_to_words(1'977) == "one thousand nine hundred seventy seven");
    REQUIRE(ps::algo::convert_to_words(2'013) == "two thousand thirteen");

    REQUIRE(ps::algo::convert_to_words(1'000'000) == "one million");
    REQUIRE(ps::algo::convert_to_words(4'256'935) ==
            "four million two hundred fifty six thousand nine hundred thirty five");

    REQUIRE(ps::algo::convert_to_words(87'162'543'956) ==
            "eighty seven billion one hundred sixty two million five hundred fourty three thousand nine hundred "
            "fifty six");
    REQUIRE(ps::algo::convert_to_words(33'091'844'110'815) ==
            "thirty three trillion ninety one billion eight hundred fourty four million one hundred ten thousand eight "
            "hundred fifteen"); // US national debt as of this writing

    REQUIRE(ps::algo::convert_to_words(10'000'000'000'000'000) == "ten quadrillion");
}
