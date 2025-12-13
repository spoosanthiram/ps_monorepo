#include "algo/other/Knapsack.h"

namespace Ps::Algo {

int knapsack(const std::vector<KnapsackItem>& items, int W)
{
    std::vector<int> m0(W, 0);
    std::vector<int> m1(W, 0);

    int len = static_cast<int>(items.size());

    for (int i = 1; i < len; ++i) {
        for (int w = 0; w < W; ++w) {
            if (items[i].weight > w) {
                m1[w] = m0[w];
            }
            else {
                m1[w] = std::max(m0[w], m0[w - items[i].weight] + items[i].value);
            }
        }
        std::copy(m1.begin(), m1.end(), m0.begin());
    }

    return m1[W - 1];
}

} // namespace Ps::Algo
