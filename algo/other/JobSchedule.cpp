#include "algo/other/JobSchedule.h"

namespace Ps::Algo {

int64_t compute_weighted_completion_time(const std::vector<Job>& jobs)
{
    int64_t weighted_completion_time = 0;
    int64_t completion_time = 0;

    for (const Job& job : jobs) {
        completion_time += job.length;
        weighted_completion_time += job.weight * completion_time;
    }

    return weighted_completion_time;
}

} // namespace Ps::Algo
