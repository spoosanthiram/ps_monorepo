#include "algo/basic/HashTable.h"

#include "algo/basic/SmallPrimes.h"

#include <cmath>

namespace Ps::Algo {

HashTable::HashTable(unsigned int num_buckets)
    : buckets_{nullptr}
    , num_buckets_{0}
    , m_size{0}
{
    num_buckets_ = get_prime_bucket_size(num_buckets);
    buckets_ = new std::forward_list<std::pair<unsigned int, int>>[num_buckets_];
}

HashTable::~HashTable()
{
    delete[] buckets_;
}

unsigned int HashTable::get_prime_bucket_size(unsigned int num_buckets)
{
    const auto power = std::log2(num_buckets);
    const auto low = static_cast<unsigned int>(std::pow(2.0, std::floor(power)));
    const auto high = static_cast<unsigned int>(std::pow(2.0, std::ceil(power)));

    auto acceptable_size = low + (high - low) / 2;

    if (num_buckets > acceptable_size) {
        for (auto n = acceptable_size; n < high; ++n) {
            if (Ps::Algo::is_prime(n)) {
                acceptable_size = n;
                break;
            }
        }
    }
    else {
        for (unsigned int n = acceptable_size; n > low; --n) {
            if (Ps::Algo::is_prime(n)) {
                acceptable_size = n;
                break;
            }
        }
    }

    return acceptable_size;
}

HashTable::iterator_t HashTable::get_iterator(bucket_t& bucket, unsigned int key) const
{
    auto it = bucket.begin();
    for (; it != bucket.end(); ++it) {
        if ((*it).first == key) {
            break;
        }
    }

    return it;
}

} // namespace Ps::Algo
