#pragma once

#include <cstdint>
#include <vector>

namespace Ps::Algo {

/// @brief EPI 6.1 India Flag Partition (aka Dutch Flag Partition)
/// @param numbers Array of integers to be partitioned
/// @param pivot_index Index of the number to be used for pivot
///
void india_flag_partition(std::vector<int>& numbers, uint32_t pivot_index);

/// @brief EPI 6.2 Increment an Arbitrary-Precision Integer
///        Example: 129 -> 130
///        Input: {1, 2, 9}  Return: {1, 3, 0}
/// @param X An integer as an array of digits
/// @return Incremented integer as an array of digits
///
std::vector<int> increment(std::vector<int> X);

/// @brief EPI 6.3 Multiply Two Arbitrary-Precision Integers
/// @param x integer as an array of digits
/// @param y integer as an array of digits
/// @return x * y as array of digits
///
std::vector<int> multiply(std::vector<int> x, std::vector<int> y);

/// @brief EPI 6.4 Advancing Through An Array
///
bool can_reach_end(const std::vector<int>& steps);

/// @brief EPI 6.5 Delete Duplicates from a Sorted Array
/// @param sorted_array Sorted array of intss
/// @return number of valid ints
///
size_t remove_dup(std::vector<int>& sorted_array);

/// @brief EPI 6.6 Buy and Sell a Stock Once
/// @param prices Array containing prices
/// @return Max profit
///
double buy_and_sell_stock_once(const std::vector<double>& prices);

/// @brief EPI 6.8 Enumerate All Primes to N
/// @param n - Up to the number for which primes to be generated
/// @return Array of primes up to and including N
///
std::vector<uint32_t> generate_primes(uint32_t n);

/// @brief EPI 6.9 Permute the Elements of an Array
///
void apply_permutation(std::vector<char>& a, std::vector<int>& perm);

/// @brief EPI 6.10 Compute the Next Permutation Based on Dictionary Ordering
/// @param perm - Current Permutation Order
/// @return Next Permutation Order of Permutation
///
std::vector<int> next_permutation(const std::vector<int>& perm);

/// @brief EPI 6.11 Sample Offline Data
///
void random_sample(std::vector<int>& a, uint32_t k);

/// @brief EPI 6.16 The Sudoku Checker Problem
/// @param sudoku 
/// @return True if sudoku is valid, False otherwise
///
bool is_valid_sudoku(const std::vector<std::vector<uint32_t>>& sudoku);

/// @brief Pascal Triangle
/// @param n
/// @return
std::vector<std::vector<int>> pascal_triangle(int n);

} // namespace Ps::Algo
