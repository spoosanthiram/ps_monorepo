#include "algo/prep/epi/Arrays.h"

#include <algorithm>
#include <cmath>
#include <limits>
#include <random>

namespace Ps::Algo {

void india_flag_partition(std::vector<int>& numbers, uint32_t pivot_index)
{
    if (numbers.empty() || pivot_index >= numbers.size()) {
        return;
    }

    const auto pivot = numbers[pivot_index]; // pivot

    auto l = &numbers[0];                  // elements before l are lower than pivot
    auto r = &numbers[numbers.size() - 1]; // elements after r are larger than pivot

    for (auto i = &numbers[0]; i <= r;) {
        if (*i < pivot) {
            std::swap(*i, *l);
            ++l;
            ++i;
        }
        else if (*i > pivot) {
            std::swap(*i, *r);
            --r;
        }
        else {
            ++i;
        }
    }
}

std::vector<int> increment(std::vector<int> X)
{
    if (X.empty()) {
        return X;
    }

    ++X.back(); // increment last digit

    for (size_t i = X.size() - 1; i > 0 && X[i] == 10; --i) {
        X[i] = 0;
        ++X[i - 1];
    }

    if (X[0] == 10) {
        X[0] = 0;
        X.insert(X.begin(), 1);
    }

    return X;
}

std::vector<int> multiply(std::vector<int> x, std::vector<int> y)
{
    if (x.empty() || y.empty()) {
        return std::vector<int>{};
    }

    std::vector<int> result;
    result.assign(x.size() + y.size(), 0);

    int sign = (x.front() < 0) ^ (y.front() < 0) ? -1 : 1;

    x[0] = std::abs(x[0]);
    y[0] = std::abs(y[0]);

    for (auto i = static_cast<int64_t>(x.size() - 1); i >= 0; --i) {
        for (auto j = static_cast<int64_t>(y.size() - 1); j >= 0; --j) {
            result[static_cast<size_t>(i + j + 1)] += x[static_cast<size_t>(i)] * y[static_cast<size_t>(j)];
            result[static_cast<size_t>(i + j)] += result[static_cast<size_t>(i + j + 1)] / 10;
            result[static_cast<size_t>(i + j + 1)] %= 10;
        }
    }

    result.erase(std::remove(result.begin(), result.end(), 0), result.end());
    result[0] *= sign;

    return result;
}

bool can_reach_end(const std::vector<int>& steps)
{
    int64_t max_index = 0;
    int64_t last_index = static_cast<int64_t>(steps.size() - 1);
    for (int64_t i = 0; i <= max_index && i < last_index; ++i) {
        max_index = std::max(max_index, i + steps[static_cast<size_t>(i)]);
    }
    return max_index >= last_index;
}

size_t remove_dup(std::vector<int>& sorted_array)
{
    if (sorted_array.empty()) {
        return 0;
    }

    size_t write_index = 1;
    for (size_t i = 1; i < sorted_array.size(); ++i) {
        if (sorted_array[write_index - 1] != sorted_array[i]) {
            sorted_array[write_index] = sorted_array[i];
            ++write_index;
        }
    }

    return write_index;
}

// Example
// Input:         {310, 315, 275, 295, 260, 270, 290, 230, 255, 250}
// Min So Far:    {310, 310, 275, 275, 260, 260, 260, 230, 230, 230}
// Profit So Far: {  0,   5,   0,  20,   9,  10,  30,   0,   5,  20}
// Max Profit:    30
double buy_and_sell_stock_once(const std::vector<double>& prices)
{
    double max_profit = 0.0;
    double min_price_so_far = std::numeric_limits<double>::max();
    for (const auto price : prices) {
        min_price_so_far = std::min(price, min_price_so_far);
        const auto current_profit = price - min_price_so_far;
        max_profit = std::max(max_profit, current_profit);
    }
    return max_profit;
}

std::vector<uint32_t> generate_primes(uint32_t n)
{
    if (n < 2) {
        return std::vector<uint32_t>{};
    }

    std::vector<uint32_t> primes;
    primes.push_back(2);

    const auto size = static_cast<uint32_t>(std::floor(0.5 * (static_cast<int32_t>(n) - 3)) + 1);
    std::vector<bool> is_prime(size, true);
    for (size_t i = 0; i < size; ++i) {
        if (is_prime[i]) {
            const auto p = static_cast<uint32_t>(2 * i + 3);
            primes.push_back(p);
            for (auto j = 2 * i * i + 6 * i + 3; j < size; j += p) {
                is_prime[j] = false;
            }
        }
    }

    return primes;
}

void apply_permutation(std::vector<char>& a, std::vector<int>& perm)
{
    if (a.size() != perm.size()) {
        return;
    }

    for (size_t i = 0; i < a.size(); ++i) {
        size_t next_index = i;
        while (perm[next_index] >= 0) {
            std::swap(a[i], a[static_cast<size_t>(perm[next_index])]);
            size_t tmp = next_index;
            next_index = static_cast<size_t>(perm[next_index]);
            perm[tmp] -= static_cast<int>(perm.size());
        }
    }

    for (auto& p : perm) {
        p += static_cast<int>(perm.size());
    }
}

// Example: {6, 2, 1, 5, 4, 3, 0}
//                 k        l
//          {6, 2, 3, 5, 4, 1, 0}
// Return:  {6, 2, 3, 0, 1, 4, 5}
std::vector<int> next_permutation(const std::vector<int>& perm)
{
    if (perm.size() <= 1) {
        return perm;
    }

    std::vector<int> next_perm{perm};

    auto k = next_perm.end() - 1;
    while (k > next_perm.begin() && *(k - 1) >= *k) {
        --k;
    }
    if (k == next_perm.begin()) { // last permutation, no more permutation
        next_perm.clear();
        return next_perm;
    }

    --k;
    auto l = next_perm.end() - 1;
    while (*l < *k) {
        --l;
    }
    std::swap(*k, *l);

    // reverse to sort
    for (auto i = k + 1, j = next_perm.end() - 1; i < j; ++i, --j) {
        std::swap(*i, *j);
    }

    return next_perm;
}

void random_sample(std::vector<int>& a, uint32_t k)
{
    std::default_random_engine engine;
    for (uint32_t i = 0; i < k; ++i) {
        uint32_t j = std::uniform_int_distribution<uint32_t>{i, static_cast<uint32_t>(a.size() - 1)}(engine);
        std::swap(a[i], a[j]);
    }
}

bool has_sudoku_duplicate(const std::vector<std::vector<uint32_t>>& sudoku,
                          uint32_t row_start,
                          uint32_t row_end,
                          uint32_t col_start,
                          uint32_t col_end)
{
    constexpr auto sudoku_size = 9u;
    static std::array<bool, sudoku_size + 1> lookup_table;

    lookup_table.fill(false);

    for (auto i = row_start; i < row_end; ++i) {
        for (auto j = col_start; j < col_end; ++j) {
            auto val = sudoku[i][j];
            if (val != 0 && lookup_table[val]) {
                return true;
            }
            lookup_table[val] = true;
        }
    }

    return false;
}

bool is_valid_sudoku(const std::vector<std::vector<uint32_t>>& sudoku)
{
    constexpr auto sudoku_grid_size = 3u;

    // check for rows
    for (uint32_t i = 0; i < sudoku.size(); ++i) {
        if (has_sudoku_duplicate(sudoku, i, i + 1, 0, static_cast<uint32_t>(sudoku[i].size()))) {
            return false;
        }
    }

    // check for columns
    for (uint32_t j = 0; j < sudoku.back().size(); ++j) {
        if (has_sudoku_duplicate(sudoku, 0, static_cast<uint32_t>(sudoku.size()), j, j + 1)) {
            return false;
        }
    }

    // check for sub grids
    for (uint32_t i = 0; i < sudoku.size(); i += sudoku_grid_size) {
        for (u_int32_t j = 0; j < sudoku[i].size(); j += sudoku_grid_size) {
            if (has_sudoku_duplicate(sudoku, i, i + sudoku_grid_size, j, j + sudoku_grid_size)) {
                return false;
            }
        }
    }

    return true;
}

std::vector<std::vector<int>> pascal_triangle(int n)
{
    std::vector<std::vector<int>> pt;

    if (n < 0) {
        return pt;
    }

    pt.emplace_back(std::vector<int>{1});

    // 0 -> 1
    // 1 -> 1, 1
    // 2 -> 1, 2, 1

    for (size_t i = 1; i <= static_cast<size_t>(n); ++i) {
        std::vector<int> current_row;
        current_row.push_back(1);

        auto& prev_row = pt.back();
        for (size_t j = 1; j < prev_row.size(); ++j) {
            current_row.push_back(prev_row[j - 1] + prev_row[j]);
        }

        current_row.push_back(1);

        pt.emplace_back(current_row);
    }

    return pt;
}

} // namespace Ps::Algo
