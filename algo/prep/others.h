#pragma once

#include <string>
#include <vector>

namespace ps::algo {

/// @brief Compute permutations
std::vector<std::string> permutations(const std::string& str);

/// @brief Skyline problem: return area
struct Building
{
    int32_t start;
    int32_t end;
    int32_t height;
};
int64_t skyline_area(const std::vector<Building>& buildings);

} // namespace ps::algo
