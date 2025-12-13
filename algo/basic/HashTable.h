#pragma once

#include <format>
#include <forward_list>
#include <stdexcept>

namespace Ps::Algo {

class HashTable
{
public:
    HashTable(unsigned int num_buckets);
    ~HashTable();

    bool is_exist(unsigned int key) const
    {
        bucket_t& bucket = get_bucket(key);
        iterator_t it = get_iterator(bucket, key);
        return it != bucket.end();
    }

    int item_at(unsigned int key) const
    {
        bucket_t& bucket = get_bucket(key);
        auto it = get_iterator(bucket, key);
        if (it == bucket.end()) {
            throw std::runtime_error{std::format("The key {} is not found in the HashTable.", key)};
        }
        return it->second;
    }

    void insert(unsigned int key, int value)
    {
        bucket_t& bucket = get_bucket(key);
        iterator_t it = get_iterator(bucket, key);
        if (it != bucket.end()) {
            throw std::runtime_error{
                std::format("The key {} is already avilable in the HashTable. Use is_exist()!", key)};
        }
        bucket.emplace_front(key, value);
        ++m_size;
    }

    void remove(unsigned int key)
    {
        bucket_t& bucket = get_bucket(key);
        iterator_t it = get_iterator(bucket, key);
        if (it == bucket.end()) {
            throw std::runtime_error{std::format("The key {} is not found in the HashTable.", key)};
        }
        bucket.remove(*it);
        --m_size;
    }

private:
    using item_t = std::pair<unsigned int, int>;
    using bucket_t = std::forward_list<item_t>;
    using iterator_t = bucket_t::iterator;

    unsigned int get_prime_bucket_size(unsigned int num_buckets);
    bucket_t& get_bucket(unsigned int key) const
    {
        const auto index = key % num_buckets_;
        return buckets_[index];
    }
    iterator_t get_iterator(bucket_t& bucket, unsigned int key) const;

    bucket_t* buckets_;
    std::size_t num_buckets_;
    std::size_t m_size;
};

} // namespace Ps::Algo
