#include "Sorting.h"

#include "Algo.h"

namespace Ps::Algo {

void insertion_sort(std::vector<int>& a)
{
    if (a.size() <= 1) {
        return;
    }

    int* pa = a.data();

    int* p = pa + 1;
    int* r = pa + a.size();
    int* q;
    for (; p < r; ++p) {
        int val = *p;
        for (q = p - 1; q >= pa && *q > val; --q) {
            *(q + 1) = *q;
        }
        *(++q) = val;
    }
}

void merge_sort(std::vector<int>& a)
{
    if (a.size() <= 1) {
        return;
    }

    std::vector<int> left_aux_mem;
    left_aux_mem.reserve(a.size() / 2 + 2);
    std::vector<int> right_aux_mem;
    right_aux_mem.reserve(a.size() / 2 + 2);

    merge_sort(&a[0], &a[a.size() - 1], left_aux_mem, right_aux_mem);
}

uint64_t quick_sort(int* p, int* r)
{
    if (p < r) {
        int* q = partition(p, r);
        const auto left_comparisons = quick_sort(p, q - 1);
        const auto right_comparisons = quick_sort(q + 1, r);

        return left_comparisons + right_comparisons + static_cast<uint64_t>(r - p);
    }

    return 0;
}

uint64_t quick_sort(std::vector<int>& a)
{
    if (a.size() <= 1) {
        return 0;
    }

    auto pa = a.data();
    return quick_sort(pa, pa + (a.size() - 1));
}

uint64_t randomized_quick_sort(int* p, int* r)
{
    if (p < r) {
        int* q = randomized_partition(p, r);
        const auto left_comparisons = randomized_quick_sort(p, q - 1);
        const auto right_comparisons = randomized_quick_sort(q + 1, r);
        return left_comparisons + right_comparisons + static_cast<uint64_t>(r - p);
    }

    return 0;
}

uint64_t randomized_quick_sort(std::vector<int>& a)
{
    if (a.size() <= 1) {
        return 0;
    }

    int* data = a.data();
    return randomized_quick_sort(data, data + (a.size() - 1));
}

} // namespace Ps::Algo
