#include "algo/basic/BinarySearchTree.ipp"
#include "algo/basic/BinaryTree.ipp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("BinarySearchTree Inorder")
{
    std::vector<int> values{7, 4, 8, 3, 5, 10, 9};
    Ps::Algo::BinarySearchTree<int> tree{values};
    std::vector<int> actual = tree.inorder();
    std::sort(values.begin(), values.end());
    REQUIRE(actual == values);
}

TEST_CASE("BinarySearchTree Inorder Non-recursive")
{
    std::vector<int> values{7, 8, 4, 5, 10, 3, 9};
    Ps::Algo::BinarySearchTree<int> tree{values};
    std::vector<int> actual = tree.inorder_non_rec();
    std::sort(values.begin(), values.end());
    REQUIRE(actual == values);
}

TEST_CASE("BinarySearchTree Preorder")
{
    std::vector<int> values{7, 8, 4, 10, 9, 3, 5};
    Ps::Algo::BinarySearchTree<int> tree{values};
    std::vector<int> actual = tree.preorder();
    std::vector<int> expected{7, 4, 3, 5, 8, 10, 9};
    REQUIRE(actual == expected);
}

TEST_CASE("BinarySearchTree Remove")
{
    /* Initial tree
            23
          /    \
        18      28
       / \     /   \
     17  21   25    31
        / \   / \
      19  N  N 27
    */
    std::vector<int> values{23, 18, 28, 17, 21, 25, 19, 31, 27};
    Ps::Algo::BinarySearchTree<int> tree{values};
    {
        std::ostringstream str_stream;
        tree.write(str_stream);
        REQUIRE(str_stream.str() == "23i,18i,17,21i,19,N,28i,25i,N,27,31,");
    }
    REQUIRE_FALSE(tree.remove(20)); // remove non exisiting value
    // remove node with no child
    {
        REQUIRE(tree.remove(19));
        std::ostringstream str_stream;
        tree.write(str_stream);
        REQUIRE(str_stream.str() == "23i,18i,17,21,28i,25i,N,27,31,");
    }
    tree.insert(29);
    tree.insert(30);
    // remove node with left child but no right child
    {
        REQUIRE(tree.remove(31));
        std::ostringstream str_stream;
        tree.write(str_stream);
        REQUIRE(str_stream.str() == "23i,18i,17,21,28i,25i,N,27,29i,N,30,");
    }
    tree.insert(22);
    // remove node with right child but no left child
    {
        REQUIRE(tree.remove(21));
        std::ostringstream str_stream;
        tree.write(str_stream);
        REQUIRE(str_stream.str() == "23i,18i,17,22,28i,25i,N,27,29i,N,30,");
    }
    // remove node with both child (no grandchild)
    {
        REQUIRE(tree.remove(23));
        std::ostringstream str_stream;
        tree.write(str_stream);
        REQUIRE(str_stream.str() == "22i,18i,17,N,28i,25i,N,27,29i,N,30,");
    }
    tree.insert(26);
    // remove node with both child and grandchild
    {
        REQUIRE(tree.remove(28));
        std::ostringstream str_stream;
        tree.write(str_stream);
        REQUIRE(str_stream.str() == "22i,18i,17,N,27i,25i,N,26,29i,N,30,");
    }
}

TEST_CASE("BinarySearchTree Most Negative In Level")
{
    std::vector<int> values{-5, -7, -2, -3, 0};
    Ps::Algo::BinarySearchTree<int> tree{values};
    auto actual = tree.max_in_level([](int value) { return value < 0; });
    std::pair<size_t, unsigned int> expected{1, 2};
    REQUIRE(actual == expected);
}
