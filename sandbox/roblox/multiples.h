#pragma once

#include "sandbox/roblox/Int.h"

#include <chrono>
#include <cstdint>
#include <iostream>
#include <set>

namespace Ps::Algo {

/// @brief Get nth number that occupies the position of the series
/// 1, 2, 3, 4, 5, 6, ...
/// The number that are multiple of 2, 3, or 5 only (not other prime factors)
/// @param nth_pos - nth position
/// @return nth position number
template <typename Type>
Type nth_multiple(uint32_t nth_pos)
{
    const auto t0 = std::chrono::system_clock::now();

    uint32_t ith_pos = 0;
    auto ith_multiple = Type{0}; // Hold the ith_pos multiple

    std::set<Type> intermediate; // std::set to keep numbers sorted & not to allow duplicate
    intermediate.insert(Type{1});
    while (ith_pos < nth_pos) {
        ith_multiple = *intermediate.begin();
        intermediate.erase(intermediate.begin());

        intermediate.insert(ith_multiple * 2);
        intermediate.insert(ith_multiple * 3);
        intermediate.insert(ith_multiple * 5);

        ++ith_pos;
    }

    const auto t1 = std::chrono::system_clock::now();

    const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
    if (ms > 60000) {
        std::cout << std::format("Time to get {}th multiple: {} minutes", nth_pos, ms / 60000) << '\n';
    }
    else if (ms > 1000) {
        std::cout << std::format("Time to get {}th multiple: {} seconds", nth_pos, ms / 1000) << '\n';
    }

    return ith_multiple;
}

/// @brief Get nth number that occupies the position of the series
/// 1, 2, 3, 4, 5, 6, ...
/// The number that are multiple of 2, 3, or 5 only (not other prime factors)
/// @param nth_pos - nth position
/// @return nth position number
Ps::Algo::Int nth_multiple_byte_stream(uint32_t nth_pos);

} // namespace Ps::Algo
