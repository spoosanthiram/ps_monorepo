#include "strings.h"

#include <algorithm>
#include <array>
#include <forward_list>

namespace {

constexpr char digit_lookup[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

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

std::string to_string_base_p2(unsigned int x, unsigned int base)
{
    std::string result;

    auto mask = base - 1;
    auto nshift = 1;
    while (base > 2) {
        ++nshift;
        base /= 2;
    }

    while (x) {
        result.push_back(digit_lookup[x & mask]);
        x >>= nshift;
    }

    std::reverse(result.begin(), result.end());

    return result;
}

std::forward_list<std::string_view>::iterator convert_3_digits_to_words(
    uint64_t x, std::forward_list<std::string_view>::iterator it, std::forward_list<std::string_view>& words_list)
{
    constexpr std::array<std::string_view, 20> upto_teen_lookup{
        "",    "one",    "two",    "three",    "four",     "five",    "six",     "seven",     "eight",    "nine",
        "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
    constexpr std::array<std::string_view, 10> tens_lookup{
        "", "", "twenty", "thirty", "fourty", "fifty", "sixty", "seventy", "eighty", "ninety"};

    const auto hundreds = upto_teen_lookup[x / 100];
    if (!hundreds.empty()) {
        it = words_list.insert_after(it, hundreds);
        it = words_list.insert_after(it, "hundred");
    }

    x %= 100;
    if (x == 0) {
        ; // nothing to do
    }
    else if (x < upto_teen_lookup.size()) {
        it = words_list.insert_after(it, upto_teen_lookup[x]);
    }
    else {
        it = words_list.insert_after(it, tens_lookup[x / 10]);
        x %= 10;
        if (x != 0) {
            it = words_list.insert_after(it, upto_teen_lookup[x]);
        }
    }

    return it;
}

} // namespace

namespace ps::algo {

bool is_palindrome(const std::string& str)
{
    if (str.size() <= 1) {
        return true;
    }

    for (size_t i = 0, j = str.size() - 1; i < j; ++i, --j) {
        if (str[i] != str[j]) {
            return false;
        }
    }

    return true;
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
            result.push_back(digit_lookup[x % base]);
            x /= base;
        }

        std::reverse(result.begin(), result.end());
    }

    return result;
}

int remove_replace(char str[], int size)
{
    // Remove 'b' & count 'a'
    int n_a = 0;
    int write_idx = 0;
    for (int i = 0; i < size; ++i) {
        if (str[i] == 'a') {
            ++n_a;
        }
        if (str[i] != 'b') {
            str[write_idx] = str[i];
            ++write_idx;
        }
    }

    size = write_idx + n_a;

    auto j = size - 1;
    while (--write_idx >= 0) {
        if (str[write_idx] == 'a') {
            str[j--] = 'd';
            str[j--] = 'd';
        }
        else {
            str[j--] = str[write_idx];
        }
    }

    return size;
}

std::string convert_to_words(uint64_t x)
{
    if (x == 0) {
        return "zero";
    }

    constexpr std::array<std::string_view, 6> group_words_lookup{
        "", "thousand", "million", "billion", "trillion", "quadrillion"};

    std::forward_list<std::string_view> words_list;
    for (auto group_index = 0u; x != 0; x /= 1000, ++group_index) {
        auto it = convert_3_digits_to_words(x % 1000, words_list.before_begin(), words_list);
        if (it != words_list.before_begin()) {
            words_list.insert_after(it, group_words_lookup[group_index]);
        }
    }

    std::string words_str;

    for (const auto& words : words_list) {
        if (!words.empty()) {
            words_str.append(words);
            words_str.append(" ");
        }
    }
    words_str.pop_back();

    return words_str;
}

} // namespace ps::algo
