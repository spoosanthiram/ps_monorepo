#include "Strings.h"

#include <array>
#include <forward_list>

namespace Ps::Algo {

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

void add_to_words(std::string_view word, std::string& words)
{
    if (!words.empty()) {
        words.append(" ");
    }
    words.append(word);
}

std::string convert_3_digits_to_words(uint64_t x)
{
    std::string words;

    constexpr std::array<std::string_view, 20> kUpto_Teen{
        "",    "one",    "two",    "three",    "four",     "five",    "six",     "seven",     "eight",    "nine",
        "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
    constexpr std::array<std::string_view, 10> kTens{
        "", "", "twenty", "thirty", "fourty", "fifty", "sixty", "seventy", "eighty", "ninety"};

    const auto hundreds = kUpto_Teen[x / 100];
    if (!hundreds.empty()) {
        words.append(hundreds);
        words.append(" hundred");
    }

    x %= 100;
    if (x == 0) {
        ; // nothing to do
    }
    else if (x < kUpto_Teen.size()) {
        add_to_words(kUpto_Teen[x], words);
    }
    else {
        add_to_words(kTens[x / 10], words);
        x %= 10;
        if (x != 0) {
            add_to_words(kUpto_Teen[x], words);
        }
    }

    return words;
}

std::string convert_to_words(uint64_t x)
{
    if (x == 0) {
        return "zero";
    }

    constexpr std::array<const char*, 6> kGroup_Words{"", "thousand", "million", "billion", "trillion", "quadrillion"};

    std::forward_list<std::string> words_list;
    for (auto group_index = 0u; x != 0; x /= 1000, ++group_index) {
        const auto sub_words = convert_3_digits_to_words(x % 1000);
        if (!sub_words.empty()) {
            auto it = words_list.insert_after(words_list.before_begin(), sub_words);
            words_list.insert_after(it, kGroup_Words[group_index]);
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

} // namespace Ps::Algo
