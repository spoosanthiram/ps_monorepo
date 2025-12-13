#include "algo/basic/Algo.h"

#include <Eigen/Core>

#include <limits>
#include <stdexcept>
#include <utility>

namespace Ps::Algo {

int64_t fibonacci(uint32_t n)
{
    int64_t f0{0};
    int64_t f1{1};

    if (n == 0) {
        return f0;
    }
    else if (n == 1) {
        return f1;
    }

    Eigen::Matrix<int64_t, 2, 2> M;
    M.setIdentity();

    Eigen::Matrix<int64_t, 2, 2> fib_matrix_i;
    fib_matrix_i << 0, 1, 1, 1;

    while (n > 0) {
        if ((n & 0x1) > 0) {
            M *= fib_matrix_i;
        }

        fib_matrix_i *= fib_matrix_i;
        n >>= 1;
    }

    const auto fn = M(0, 0) * f0 + M(0, 1) * f1;
    return fn;
}

bool is_palindrome(int32_t x)
{
    if (x < 0) {
        return false;
    }

    int32_t x2 = x;

    int32_t y = 0;
    while (x2 > 0) {
        y = y * 10 + x2 % 10;
        x2 /= 10;
    }

    return x == y;
}

int64_t linear_search(const std::vector<int>& numbers, int x)
{
    for (size_t i = 0; i < numbers.size(); ++i) {
        if (numbers[i] == x) {
            return static_cast<int64_t>(i);
        }
    }
    return -1;
}

int64_t binary_search(const std::vector<int>& numbers, int x)
{
    if (numbers.empty()) {
        return -1;
    }

    const auto data = numbers.data();

    const auto* l = data;
    const auto* u = &data[numbers.size() - 1];
    while (l <= u) {
        const auto* m = l + (u - l + 1) / 2;
        if (x == *m) {
            return m - data;
        }
        else if (x < *m) {
            u = m - 1;
        }
        else {
            l = m + 1;
        }
    }

    return -1;
}

int64_t maximum_subarray(const std::vector<int>& numbers, int64_t& start_index, int64_t& end_index)
{
    if (numbers.empty()) {
        return 0;
    }

    const int* data = numbers.data();

    start_index = end_index = 0;

    int64_t max_ending_here = 0;
    int64_t max_so_far = 0;
    const int* start_index_candidate = data;

    const int* end = data + numbers.size();
    for (const int* i = data; i < end; ++i) {
        max_ending_here += *i;

        if (max_ending_here < 0) {
            max_ending_here = 0;
            start_index_candidate = i + 1;
        }
        else if (max_ending_here > max_so_far) {
            max_so_far = max_ending_here;
            start_index = start_index_candidate - data;
            end_index = i - data;
        }
    }

    return max_so_far;
}

int* partition(int* p, int* r)
{
    int* i = p;
    for (int* j = p; j < r; ++j) {
        if (*j <= *r) {
            std::swap(*i, *j);
            ++i;
        }
    }
    std::swap(*i, *r);
    return i;
}

int* randomized_partition(int* p, int* r)
{
    auto i = std::rand() % (r - p + 1);
    std::swap(*(p + i), *r);
    return partition(p, r);
}

// Helper function for select (order statistics)
int select(int* p, int* r, size_t i)
{
    if (p == r) {
        return *p;
    }

    int* q = randomized_partition(p, r);
    auto k = static_cast<size_t>(q - p);
    if (i == k) {
        return *q;
    }
    else if (i < k) {
        return select(p, q - 1, i);
    }
    else {
        return select(q + 1, r, i - k - 1);
    }
}

int select(std::vector<int>& numbers, size_t i)
{
    if (numbers.empty() || i >= numbers.size()) {
        throw std::runtime_error{"Index out of range"};
    }

    int* data = numbers.data();
    return select(&data[0], &data[numbers.size() - 1], i);
}

uint64_t merge(int* p, int* q, int* r, std::vector<int>& left_aux_mem, std::vector<int>& right_aux_mem)
{
    left_aux_mem.clear();
    for (int* k = p; k <= q; ++k) {
        left_aux_mem.push_back(*k);
    }
    left_aux_mem.push_back(std::numeric_limits<int>::max());

    right_aux_mem.clear();
    for (int* k = q + 1; k <= r; ++k) {
        right_aux_mem.push_back(*k);
    }
    right_aux_mem.push_back(std::numeric_limits<int>::max());

    uint64_t inversions = 0;
    int* left_end = &left_aux_mem[left_aux_mem.size() - 1];

    int* i = &left_aux_mem[0];
    int* j = &right_aux_mem[0];
    for (int* k = p; k <= r; ++k) {
        if (*i <= *j) {
            *k = *i;
            ++i;
        }
        else {
            inversions += static_cast<uint64_t>(left_end - i);
            *k = *j;
            ++j;
        }
    }

    return inversions;
}

uint64_t merge_sort(int* p, int* r, std::vector<int>& left_aux_mem, std::vector<int>& right_aux_mem)
{
    if (r > p) {
        int* q = p + (r - p) / 2;
        const auto left_inversions = merge_sort(p, q, left_aux_mem, right_aux_mem);
        const auto right_inversions = merge_sort(q + 1, r, left_aux_mem, right_aux_mem);
        const auto split_inversions = merge(p, q, r, left_aux_mem, right_aux_mem);

        return left_inversions + right_inversions + split_inversions;
    }

    return 0;
}

uint64_t inversions(std::vector<int>& numbers)
{
    if (numbers.size() <= 1) {
        return 0;
    }

    std::vector<int> left_aux_mem;
    left_aux_mem.reserve((numbers.size() / 2) + 2);

    std::vector<int> right_aux_mem;
    right_aux_mem.reserve((numbers.size() / 2) + 2);

    return merge_sort(&numbers[0], &numbers[numbers.size() - 1], left_aux_mem, right_aux_mem);
}

} // namespace Ps::Algo
