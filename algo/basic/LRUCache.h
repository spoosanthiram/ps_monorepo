#pragma once

#include <list>
#include <map>

namespace Ps::Algo {

class LRUCache
{
public:
    using KeyType = int;
    using ValueType = int;

    struct Node
    {
        Node(ValueType val, std::list<KeyType>::iterator pos)
            : value{val}
            , position{pos}
        {}
        ValueType value;
        std::list<KeyType>::iterator position;
    };

public:
    LRUCache() = default;
    ~LRUCache() = default;

    bool has_key(KeyType key) const { return key_val_map_.contains(key); }

    void insert(KeyType key, ValueType value);
    ValueType lookup(KeyType key);

private:
    void move_front(KeyType key, std::map<KeyType, Node>::iterator it);

private:
    std::map<KeyType, Node> key_val_map_{};
    std::list<KeyType> lru_{};
};

} // namespace Ps::Algo
