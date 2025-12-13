#include "LRUCache.h"

#include <stdexcept>

namespace Ps::Algo {

constexpr auto kCapacity = 5;

void LRUCache::insert(KeyType key, ValueType value)
{
    auto it = key_val_map_.find(key);
    if (it != key_val_map_.end()) {
        move_front(key, it);
    }
    else {
        if (key_val_map_.size() == kCapacity) {
            key_val_map_.erase(lru_.back());
            lru_.pop_back();
        }
        lru_.push_front(key);
        key_val_map_.emplace(key, Node{value, lru_.begin()});
    }
}

LRUCache::ValueType LRUCache::lookup(KeyType key)
{
    auto it = key_val_map_.find(key);
    if (it == key_val_map_.end()) {
        throw std::logic_error{"Key not found!"};
    }

    ValueType value = it->second.value;
    move_front(key, it);
    return value;
}

void LRUCache::move_front(KeyType key, std::map<KeyType, Node>::iterator it)
{
    lru_.erase(it->second.position);
    lru_.push_front(key);
    it->second.position = lru_.begin();
}

} // namespace Ps::Algo
