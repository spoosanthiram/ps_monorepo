#include "core/utils/Base64.h"

#include <array>
#include <stdexcept>

namespace Ps::Core {

constexpr std::array<int32_t, 128> decode_lookup = {
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,   // 00 - 15
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,   // 16 - 31
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 62, -1, 62, -1, 63,   // 32 - 47
    52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1, -1, -1, -1,   // 48 - 63
    -1, 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,   // 64 - 79
    15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, 63,   // 80 - 95
    -1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,   // 96 - 111
    41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, -1, -1, -1, -1, -1};  // 112 - 127

int32_t base64_char_to_value(char ch)
{
    auto val = decode_lookup[ch & 0x7f];
    if (val == -1) {
        throw std::domain_error{"Invalid base64 character"};
    }
    return val;
}

std::vector<unsigned char> base64_decode(std::string_view base64_str)
{
    for (int count = 2; count > 0; --count) {
        if (base64_str.ends_with('=')) {
            base64_str.remove_suffix(1);
        }
    }

    std::vector<unsigned char> decoded;

    auto bits_to_decode = 0;
    int32_t bits = 0;
    for (const auto ch : base64_str) {
        bits <<= 6;
        bits += base64_char_to_value(ch);
        bits_to_decode += 6;

        if (bits_to_decode >= 8) {
            decoded.push_back(static_cast<unsigned char>(bits >> (bits_to_decode - 8)));
            bits_to_decode -= 8;
        }
    }

    return decoded;
}

}  // namespace Ps::Core
