#pragma once

#include <cstdint>
#include <string>

namespace Ps::Algo {

/// @brief Check the input string is palindrome or not
/// @param str
/// @return True if palindrome, false otherwise
bool is_palindrome(const std::string& str);

/// @brief Remove 'b' and replace 'a' with two 'd's
///        Ex: {a, c, d, b, b, c, a} -> {d, d, c, d, c, d, d}
/// @param str Array of chars
/// @param size 
/// @return Final size
int remove_replace(char str[], int size);

/// @brief Facebook Phone Interview: number to words
///        Example: 783 ==> seven hundred and eighty three
///                 27512 ==> twenty seven thousand five hundred and twelve
std::string convert_to_words(uint64_t x);

} // namespace Ps::Algo
