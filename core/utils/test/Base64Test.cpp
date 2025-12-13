#include "core/utils/Base64.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Base64 Char_To_Value")
{
    REQUIRE_THROWS(Ps::Core::base64_char_to_value('!'));

    REQUIRE(Ps::Core::base64_char_to_value('+') == 62);
    REQUIRE(Ps::Core::base64_char_to_value('-') == 62);
    REQUIRE(Ps::Core::base64_char_to_value('/') == 63);

    REQUIRE(Ps::Core::base64_char_to_value('0') == 52);
    REQUIRE(Ps::Core::base64_char_to_value('2') == 54);
    REQUIRE(Ps::Core::base64_char_to_value('5') == 57);
    REQUIRE(Ps::Core::base64_char_to_value('7') == 59);
    REQUIRE(Ps::Core::base64_char_to_value('9') == 61);

    REQUIRE_THROWS(Ps::Core::base64_char_to_value('='));

    REQUIRE(Ps::Core::base64_char_to_value('A') == 0);
    REQUIRE(Ps::Core::base64_char_to_value('M') == 12);
    REQUIRE(Ps::Core::base64_char_to_value('P') == 15);
    REQUIRE(Ps::Core::base64_char_to_value('S') == 18);
    REQUIRE(Ps::Core::base64_char_to_value('T') == 19);
    REQUIRE(Ps::Core::base64_char_to_value('Z') == 25);

    REQUIRE(Ps::Core::base64_char_to_value('_') == 63);

    REQUIRE(Ps::Core::base64_char_to_value('a') == 26);
    REQUIRE(Ps::Core::base64_char_to_value('e') == 30);
    REQUIRE(Ps::Core::base64_char_to_value('i') == 34);
    REQUIRE(Ps::Core::base64_char_to_value('q') == 42);
    REQUIRE(Ps::Core::base64_char_to_value('x') == 49);
    REQUIRE(Ps::Core::base64_char_to_value('z') == 51);

    REQUIRE_THROWS(Ps::Core::base64_char_to_value('~'));
}

TEST_CASE("Base64 Decode")
{
    {
        const auto decoded_buf = Ps::Core::base64_decode("SGVsbG8gV29ybGQh");
        std::string_view decoded_str{reinterpret_cast<const char*>(decoded_buf.data()), decoded_buf.size()};
        REQUIRE(decoded_str == "Hello World!");
    }

    {
        const auto decoded_buf = Ps::Core::base64_decode("SGVsbG8gU2FyYXZhbmFuIQ==");
        std::string_view decoded_str{reinterpret_cast<const char*>(decoded_buf.data()), decoded_buf.size()};
        REQUIRE(decoded_str == "Hello Saravanan!");
    }

    {
        const auto decoded_buf = Ps::Core::base64_decode("TWFkaHVyYSBUaGFudXJhIFM=");
        std::string_view decoded_str{reinterpret_cast<const char*>(decoded_buf.data()), decoded_buf.size()};
        REQUIRE(decoded_str == "Madhura Thanura S");
    }
}
