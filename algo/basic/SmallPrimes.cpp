#include "algo/basic/SmallPrimes.h"

#include <algorithm>
#include <format>
#include <stdexcept>

namespace Ps::Algo {

SmallPrimes::SmallPrimes(uint32_t N)
    : N_{N}
{
    primes_.push_back(2);

    last_index_ = (N - 3) / 2;

    std::vector<bool> is_prime(last_index_ + 1, true);
    for (size_t i = 0; i < is_prime.size(); ++i) {
        if (is_prime[i]) {
            uint32_t p = 2 * static_cast<uint32_t>(i) + 3;
            primes_.push_back(p);
            for (size_t j = (2 * i * i + 6 * i + 3); j < is_prime.size(); j += p) {
                is_prime[j] = false;
            }
        }
    }
}

uint32_t SmallPrimes::get_prime(uint32_t i)
{
    while (i >= primes_.size()) {
        std::vector<bool> is_prime(N_ / 2, true);
        N_ *= 2;
        for (size_t k = 1; k < primes_.size() && (primes_[k] * primes_[k]) <= N_; ++k) {
            auto p = primes_[k];
            size_t index = ((last_index_ / p) * p) + ((p - 3) / 2);
            if (index <= last_index_) {
                index += p;
            }
            for (index -= (last_index_ + 1); index < is_prime.size(); index += p) {
                is_prime[index] = false;
            }
        }

        for (size_t k = 0; k < is_prime.size(); ++k) {
            if (is_prime[k]) {
                uint32_t p = 2 * static_cast<uint32_t>(k + last_index_ + 1) + 3;
                primes_.push_back(p);
            }
        }

        last_index_ += is_prime.size() - 1;
    }

    return primes_[i];
}

bool is_prime(uint32_t n)
{
    constexpr auto kFirst_Prime = 2;
    if (n < kFirst_Prime) {
        return false;
    }

    SmallPrimes sp;
    const auto& primes = sp.current_primes();
    const auto last_prime_computed = primes.back();

    if (const auto x = last_prime_computed * last_prime_computed; n > x) {
        throw std::domain_error{std::format("is_prime() is not designed to check a number bigger than {}.", x)};
    }

    if (n <= last_prime_computed) {
        return std::binary_search(primes.cbegin(), primes.cend(), n);
    }

    for (const auto p : primes) {
        if (n % p == 0) {
            return false;
        }
    }

    return true;
}

} // namespace Ps::Algo
