#pragma once

#include <vector>

namespace Ps::Algo {

/// @brief Knapsack structure
struct KnapsackItem
{
    KnapsackItem(int v, int w)
        : value{v}
        , weight{w}
    {}
    int value;
    int weight;
};

/// @brief Knapsack
int knapsack(const std::vector<KnapsackItem>& items, int W);

} // namespace Ps::Algo
