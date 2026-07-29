#include "algo/basic/binary_search_tree.h"
#include "algo/prep/epi/binary_trees.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("binary_trees is_balanced")
{
    ps::algo::BinarySearchTree<int> tree{
        std::vector<int>{5, 2, 9, 1, 4, 7, 8}
    };
    CHECK(ps::algo::is_balanced(tree));
    tree.insert(10);
    tree.insert(11);
    tree.insert(12);
    CHECK_FALSE(ps::algo::is_balanced(tree));
}

TEST_CASE("binary_trees least_common_ancestor")
{
    ps::algo::BinarySearchTree<int> tree{
        std::vector<int>{9, 6, 15, 8, 21, 14, 10}
    };
    //           9
    //     6           15
    //  8           14    21
    //           10
    const auto actual = ps::algo::least_common_ancestor(tree, 10, 21);
    REQUIRE(actual == std::pair<bool, int>{true, 15});
}
