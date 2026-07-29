#include "binary_trees.h"

namespace ps::algo {

bool is_balanced(const BinaryTree<int>& tree)
{
    return tree.is_balanced();
}

std::pair<bool, int> least_common_ancestor(const ps::algo::BinaryTree<int>& tree, int a, int b)
{
    return tree.least_common_ancestor(a, b);
}

} // namespace ps::algo
