#include "project_euler/ProblemSet01.h"

#include "algo/basic/Algo.h"
#include "algo/basic/SmallPrimes.h"

#include <algorithm>
#include <array>
#include <cmath>

namespace Ps::ProjectEuler {

int64_t multiple_3_and_5(int32_t N)
{
    // Using arithmetic progression
    // when a_1 is first number & a_n = a_1 + (n-1)*d where d is distance between successive number
    // sum = (n * (a_1 + a_n)) / 2
    //
    // Ans: sums of 3s + sums of 5s - sums of 15s
    // since 15s counted twice on both 3s & 5s

    std::array<int64_t, 3> sums;

    std::array<int32_t, 3> distances{3, 5, 15};
    for (size_t i = 0; i < distances.size(); ++i) {
        auto d = distances[i];
        auto n = (N - 1) / d;

        int64_t a_1 = d;
        int64_t a_n = n * d; // form a_1 + (n - 1) * d == d + (n - 1) * d == n * d

        sums[i] = (n * (a_1 + a_n)) / 2;
    }

    return (sums[0] + sums[1]) - sums[2];
}

int64_t largest_prime_factor(int64_t n)
{
    auto root = static_cast<uint32_t>(std::sqrt(n) + 1);
    Algo::SmallPrimes sp{root};

    const auto& primes = sp.current_primes();
    for (size_t i = 0; i < sp.num_primes() && primes[i] < root && primes[i] < n; ++i) {
        while (n % primes[i] == 0 && n != primes[i]) {
            n /= primes[i];
        }
    }
    return n;
}

int32_t largest_palindrome_product()
{
    // Six digit palindrome: abccba
    //   => 100,000 * a + 10,000 * b + 1,000 * c + 100 * c + 10 * b + a
    //   => 100,001 * a + 10,010 * b + 1,100 * c
    //   => 11 * (9091 * a + 910 * b + 100 * c)
    //   => abccba is divisable by 11
    //
    int smallest_palin = 101'101;

    int max_palin = 0;
    for (int i = 999; i >= 100; --i) {
        int j = i; // start from i so we can avoid i * j == j * i duplicates
        // find next 11 multiple
        while ((j % 11) != 0) {
            --j;
        }
        int min_j = std::max(100, 100'000 / i);
        for (; j >= min_j; j -= 11) {
            int x = i * j;
            if (x < max_palin || x < smallest_palin) {
                break; // no need to go for smaller j's
            }
            if (Algo::is_palindrome(x)) {
                max_palin = x;
            }
        }
    }
    return max_palin;
}

uint32_t smallest_multiple(uint32_t n)
{
    Algo::SmallPrimes sp{n};
    const auto& primes = sp.current_primes();

    uint32_t multiple = 1;
    for (uint32_t i = 0; i < primes.size() && primes[i] <= n; ++i) {
        uint32_t pk = 1;
        while (pk * primes[i] <= n) {
            pk *= primes[i];
        }
        multiple *= pk;
    }
    return multiple;
}

int64_t num_product(std::string_view num, size_t begin_i, size_t end_i)
{
    int64_t product = 1;
    for (size_t i = begin_i; i < end_i; ++i) {
        product *= num[i] - '0';
    }
    return product;
}

int64_t largest_product(std::string_view num, uint32_t k)
{
    int64_t product = num_product(num, 0, k);

    int64_t max_product = product;
    for (size_t i = k; i < num.size(); ++i) {
        if (product == 0) {
            auto end_it = num.begin() + (i + 1);
            auto it = std::find(num.begin() + (i - k + 1), end_it, '0');
            if (it == end_it) {
                product = num_product(num, i - k + 1, i + 1);
            }
        }
        else {
            product /= num[i - k] - '0';
            product *= num[i] - '0';
        }

        if (product > max_product) {
            max_product = product;
        }
    }

    return max_product;
}

} // namespace Ps::ProjectEuler
