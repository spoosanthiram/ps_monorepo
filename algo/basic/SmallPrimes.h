#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

namespace Ps::Algo {

class SmallPrimes
{
public:
    SmallPrimes(uint32_t N = 100'000);

    size_t num_primes() const { return primes_.size(); }
    const std::vector<uint32_t>& current_primes() const { return primes_; }
    uint32_t get_prime(uint32_t i);

private:
    uint32_t N_;
    size_t last_index_{0};
    std::vector<uint32_t> primes_;
};

/// @brief Check n is prime or not
bool is_prime(uint32_t n);

} // namespace Ps::Algo
