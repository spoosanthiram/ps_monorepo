#pragma once

#include <cstdint>
#include <vector>

namespace Ps::Algo {

void insertion_sort(std::vector<int>& a);

void merge_sort(std::vector<int>& a);

void heap_sort(std::vector<int>& a);

uint64_t quick_sort(int* p, int* r);
uint64_t quick_sort(std::vector<int>& a);

uint64_t randomized_quick_sort(int* p, int* r);
uint64_t randomized_quick_sort(std::vector<int>& a);

} // namespace Ps::Algo
