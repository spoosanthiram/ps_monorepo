#include "algo/basic/Trie.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Trie Simple")
{
    Ps::Algo::Trie trie;
    trie.insert("she", 0);
    trie.insert("sells", 1);
    trie.insert("sea", 2);
    trie.insert("shells", 3);
    trie.insert("by", 4);
    trie.insert("the", 5);
    trie.insert("shore", 6);

    CHECK(trie.value("by") == 4);

    std::vector<std::string> expected;
    expected.push_back("she");
    expected.push_back("shells");
    expected.push_back("shore");

    const auto result = trie.keys_with_prefix("sh");
    CHECK(result == expected);
}
