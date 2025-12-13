#include "algo/basic/BinaryTree.ipp"
#include "core/utils/Utils.h"

#include <catch2/catch_test_macros.hpp>

#include <iostream>
#include <sstream>

TEST_CASE("BinaryTree Read")
{
    /*
           9
          /  \
        6     15
       /\     / \
      8  N   14  21
             /\
           10  N
    */
    auto input_stream = Ps::Core::open_stream("algo/basic/test/data/BinaryTree.txt");
    Ps::Algo::BinaryTree<int> tree;
    tree.read(input_stream);
    std::vector<int> expected{8, 6, 9, 10, 14, 15, 21};
    std::vector<int> nodes = tree.inorder();
    REQUIRE(nodes == expected);
}

TEST_CASE("BinaryTree Write")
{
    auto input_stream = Ps::Core::open_stream("algo/basic/test/data/BinaryTree.txt");
    Ps::Algo::BinaryTree<int> tree;
    tree.read(input_stream);

    std::ostringstream str_stream;
    tree.write(str_stream);
    auto expected = std::string{"9i,6i,8,N,15i,14i,10,N,21,"};
    REQUIRE(str_stream.str() == expected);
}
