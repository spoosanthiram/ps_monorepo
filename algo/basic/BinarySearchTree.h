#pragma once

#include "BinaryTree.h"

#include "core/utils/ClassHelper.h"

namespace Ps::Algo {

template <typename NodeType>
class BinarySearchTree : public BinaryTree<NodeType>
{
public:
    BinarySearchTree();
    BinarySearchTree(const std::vector<int>& numbers);
    ~BinarySearchTree() = default;

    COPY_CONSTRUCTOR(BinarySearchTree) = delete;
    MOVE_CONSTRUCTOR(BinarySearchTree) = default;
    COPY_ASSIGNMENT(BinarySearchTree) = delete;
    MOVE_ASSIGNMENT(BinarySearchTree) = delete;

    void insert(const NodeType& value);
    bool remove(const NodeType& value);
    void build_balanced(const std::vector<int>& sorted);

private:
    BinaryTreeNode<NodeType>*& find(const NodeType& value);
    void remove(BinaryTreeNode<NodeType>*& node);
    BinaryTreeNode<NodeType>*& inorder_predecessor(BinaryTreeNode<NodeType>*& node);
    void build_balanced(const int* p, const int* r, BinaryTreeNode<NodeType>** node);
};

} // namespace Ps::Algo
