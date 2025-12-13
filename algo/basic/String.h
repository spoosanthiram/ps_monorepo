#pragma once

#include <string>

namespace Ps::Algo {

/// @brief Convert the string str in a base to integer
/// example:
///     "2307" -> 2307
///     "aa" -> 170
int stoi(const std::string& str, int base);

/// @brief Convert the integer x in base to string
std::string to_string(unsigned int x, unsigned int base);

} // namespace Ps::Algo
