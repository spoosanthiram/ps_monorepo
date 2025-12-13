#include "algo/prep/HackerRank.h"

#include <algorithm>
#include <iostream>

namespace Ps::Algo {

int rank_score(std::vector<int>& unique_ranks, int score)
{
    int lo = 0;
    int hi = static_cast<int>(unique_ranks.size() - 1);
    while (lo <= hi) {
        int mid = hi - (hi - lo) / 2;
        if (score == unique_ranks[static_cast<size_t>(mid)]) {
            return mid + 1;
        } else if (score > unique_ranks[static_cast<size_t>(mid)]) {
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }

    if (lo == static_cast<int>(unique_ranks.size())) {
        unique_ranks.push_back(score);
        return static_cast<int>(unique_ranks.size());
    }

    auto insert_before_it = unique_ranks.begin();
    std::advance(insert_before_it, std::max(lo, hi));
    const auto inserted_pos_it = unique_ranks.insert(insert_before_it, score);
    return static_cast<int>(std::distance(unique_ranks.begin(), inserted_pos_it) + 1);
}

std::vector<int> climb_leaderboard(const std::vector<int>& ranks, const std::vector<int>& player_scores)
{
    std::vector<int> unique_ranks{ranks};
    unique_ranks.erase(std::unique(unique_ranks.begin(), unique_ranks.end()), unique_ranks.end());

    std::vector<int> player_ranks;
    for (const auto score : player_scores) {
        player_ranks.push_back(rank_score(unique_ranks, score));
    }

    return player_ranks;
}

} // namespace Ps::Algo
