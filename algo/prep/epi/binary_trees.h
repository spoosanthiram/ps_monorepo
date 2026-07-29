#pragma once

#include "algo/basic/binary_tree.h"

namespace ps::algo {

/// @brief EPI 10.1: Test if a binary tree is height-balanced
bool is_balanced(const BinaryTree<int>& tree);

/// @brief Compute the Lowest Common Ancester in a Binary Tree
std::pair<bool, int> least_common_ancestor(const ps::algo::BinaryTree<int>& tree, int a, int b);

} // namespace ps::algo
