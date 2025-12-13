#include "algo/basic/LRUCache.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("LRUCacheTest Simple")
{
    Ps::Algo::LRUCache cache;

    // add first 5
    cache.insert(7, 19);
    cache.insert(0, 2);
    cache.insert(1, 3);
    cache.insert(2, 5);
    cache.insert(3, 7);
    // current cache: 3, 2, 1, 0, 7

    CHECK(cache.has_key(0));
    CHECK(cache.lookup(0) == 2);
    // current cache: 0, 3, 2, 1, 7

    CHECK_FALSE(cache.has_key(4));
    cache.insert(4, 11);
    // current cache: 4, 0, 3, 2, 1
    CHECK_FALSE(cache.has_key(7));

    CHECK(cache.has_key(2));
    CHECK(cache.lookup(2) == 5);
    // current cache: 2, 4, 0, 3, 1
}
