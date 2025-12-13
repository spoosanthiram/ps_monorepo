#include "String.h"

#include <algorithm>

namespace Ps::Algo {

constexpr char kDigit_Lookup[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

inline bool is_decimal_digit(char c)
{
    return c >= '0' && c <= '9';
}

inline bool is_upper_hex_digit(char c)
{
    return (c >= 'A' && c <= 'F');
}

inline bool is_lower_hex_digit(char c)
{
    return (c >= 'a' && c <= 'f');
}

int stoi(const std::string& str, int base)
{
    if (str.empty()) {
        return 0;
    }

    int result = 0;

    auto i = str.begin();

    bool is_negative = false;
    if (*i == '-') {
        is_negative = true;
        ++i;
    }

    int d = 0;
    for (; i < str.end(); ++i) {
        if (is_decimal_digit(*i)) {
            d = *i - '0';
        }
        else if (is_upper_hex_digit(*i)) {
            d = *i - 'A' + 10;
        }
        else if (is_lower_hex_digit(*i)) {
            d = *i - 'a' + 10;
        }
        else {
            break; // invalid char
        }

        if (d >= base) {
            break; // invalid for the base
        }

        result = result * base + d;
    }

    return is_negative ? -result : result;
}

std::string to_string_base_p2(unsigned int x, unsigned int base)
{
    std::string result;

    if (base < 2 || base > 16 || base & (base - 1)) { // check for base and power of 2
        return result;
    }

    auto mask = base - 1;
    auto nshift = 1;
    while (base > 2) {
        ++nshift;
        base /= 2;
    }

    while (x) {
        result.push_back(kDigit_Lookup[x & mask]);
        x >>= nshift;
    }

    std::reverse(result.begin(), result.end());

    return result;
}

std::string to_string(unsigned int x, unsigned int base)
{
    std::string result;

    if (base < 2 || base > 16) {
        return result;
    }

    if (!(base & (base - 1))) {
        result = to_string_base_p2(x, base);
    }
    else {
        while (x) {
            result.push_back(kDigit_Lookup[x % base]);
            x /= base;
        }

        std::reverse(result.begin(), result.end());
    }

    return result;
}

} // namespace Ps::Algo
