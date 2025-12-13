#pragma once

#include <cstdint>
#include <vector>

namespace Ps::Algo {

/// @brief Check the year is leap year or not
constexpr bool is_leap_year(uint32_t year)
{
    return ((year % 400 == 0) || ((year % 100 != 0) && (year % 4 == 0))) ? true : false;
}

/// @brief Computes the nth fibonacci number
int64_t fibonacci(uint32_t n);

/// @brief Check given number is palindrome
bool is_palindrome(int32_t x);

/// @brief Linear search
/// @param numbers input array
/// @param x key to search
/// Returns index of the element if found otherwise returns -1
int64_t linear_search(const std::vector<int>& numbers, int x);

/// @brief binary search
/// @param numbers - sorted (non-decreasing) input array
/// @param x - key to search
/// Returns index of the element if found otherwise returns -1
int64_t binary_search(const std::vector<int>& numbers, int x);

/// @brief Finds the maximum sub array.
/// @param numbers input array
/// Returns, maximum sub array value. 0 implies the result set is empty.
/// Otherwise, start_index and end_index will point to the starting and
/// ending indices of maximum sub array.
int64_t maximum_subarray(const std::vector<int>& numbers, int64_t& start_index, int64_t& end_index);

/// @brief Partition routines used in quicksort and order statistics
/// @param p points to the first element
/// @param r points to the last element
int* partition(int* p, int* r);

/// @brief Randomized partition
int* randomized_partition(int* p, int* r);

/// @brief Selects the ith value from the unsorted sequence.
/// @param numbers input array
/// @param i ith value to find
/// Returns the value at ith index for the sequence as if it were sorted.
int select(std::vector<int>& numbers, size_t i);

/// @brief merge routine used for merge sort and counting inversions
uint64_t merge(int* p, int* q, int* r, std::vector<int>& left_aux_mem, std::vector<int>& right_aux_mem);

/// @brief merge sort helper
uint64_t merge_sort(int* p, int* r, std::vector<int>& left_aux_mem, std::vector<int>& right_aux_mem);

/// @brief Counts the inversions
uint64_t inversions(std::vector<int>& numbers);

} // namespace Ps::Algo
