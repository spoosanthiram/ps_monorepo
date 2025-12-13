#pragma once

#include <cstdint>
#include <vector>

namespace Ps::Algo {

/// @brief Job structure for completion time algorithm
struct Job
{
    Job(int w, int l)
        : weight{w}
        , length{l}
    {}
    int weight;
    int length;
};

/// @brief Compute weighted completion time
int64_t compute_weighted_completion_time(const std::vector<Job>& jobs);

} // namespace Ps::Algo
