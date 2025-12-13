#include "sandbox/roblox/multiples.h"

#include <format>

namespace Ps::Algo {

Ps::Algo::Int nth_multiple_byte_stream(uint32_t nth_pos)
{
    const auto t0 = std::chrono::system_clock::now();

    uint32_t ith_pos = 0;
    auto ith_multiple = Ps::Algo::Int{0}; // Hold the ith_pos multiple

    std::set<Ps::Algo::Int> intermediate; // std::set to keep numbers sorted & not to allow duplicate
    intermediate.insert(Ps::Algo::Int{1});
    Ps::Algo::Int x2, x3, x5;
    while (ith_pos < nth_pos) {
        ith_multiple = *intermediate.begin();
        intermediate.erase(intermediate.begin());

        x2 = ith_multiple.twice();
        x3 = x2 + ith_multiple;
        x5 = x3 + x2;

        intermediate.insert(x2);
        intermediate.insert(x3);
        intermediate.insert(x5);

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

} // namespace Ps::Algo
