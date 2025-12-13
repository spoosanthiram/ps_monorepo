#include "algo/prep/HackerRank.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("HackerRank ClimbingLeaderboard")
{
    std::vector<int> ranks{100, 100, 50, 40, 40, 20, 10};
    std::vector<int> player_scores{5, 25, 50, 120};
    const auto player_ranks = Ps::Algo::climb_leaderboard(ranks, player_scores);
    REQUIRE(player_ranks == std::vector<int>{6, 4, 2, 1});
}

TEST_CASE("HackerRank ClimbingLeaderboard2")
{
    std::vector<int> ranks{100, 90, 90, 80, 75, 60};
    std::vector<int> player_scores{50, 65, 77, 90, 102};
    const auto player_ranks = Ps::Algo::climb_leaderboard(ranks, player_scores);
    REQUIRE(player_ranks == std::vector<int>{6, 5, 4, 2, 1});
}
