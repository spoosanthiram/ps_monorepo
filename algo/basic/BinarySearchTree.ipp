#pragma once

#include "BinarySearchTree.h"

#include <spdlog/spdlog.h>

namespace Ps::Algo {

template <typename NodeType>
BinarySearchTree<NodeType>::BinarySearchTree(const std::vector<int>& numbers)
    : BinaryTree<NodeType>{}
{
    for (auto i : numbers) {
        insert(i);
    }
}

template <typename NodeType>
void BinarySearchTree<NodeType>::insert(const NodeType& value)
{
    BinaryTreeNode<NodeType>** node = &BinaryTree<NodeType>::root();
    while (*node) {
        if (value < (*node)->value) {
            node = &(*node)->left;
        }
        else {
            node = &(*node)->right;
        }
    }
    *node = new BinaryTreeNode<NodeType>{value};
}

template <typename NodeType>
bool BinarySearchTree<NodeType>::remove(const NodeType& value)
{
    auto& node = find(value);
    if (!node) {
        SPDLOG_WARN("{} not in the tree", value);
        return false;
    }
    remove(node);
    return true;
}

template <typename NodeType>
void BinarySearchTree<NodeType>::build_balanced(const std::vector<int>& sorted)
{
    const int* p = sorted.data();
    const int* r = &p[sorted.size() - 1];
    auto& root_node = BinaryTree<NodeType>::root();
    build_alanced(p, r, &root_node);
}

template <typename NodeType>
BinaryTreeNode<NodeType>*& BinarySearchTree<NodeType>::find(const NodeType& value)
{
    BinaryTreeNode<NodeType>** node = &BinaryTree<NodeType>::root();
    while (*node) {
        if ((*node)->value == value) {
            break;
        }
        else if ((*node)->value > value) {
            node = &(*node)->left;
        }
        else {
            node = &(*node)->right;
        }
    }
    return *node;
}

template <typename NodeType>
void BinarySearchTree<NodeType>::remove(BinaryTreeNode<NodeType>*& node)
{
    if (!node->left && !node->right) {
        delete node;
        node = nullptr;
    }
    else if (node->left && !node->right) {
        auto tmp = node;
        node = node->left;
        delete tmp;
    }
    else if (!node->left && node->right) {
        auto tmp = node;
        node = node->right;
        delete tmp;
    }
    else {
        auto& iop_node = inorder_predecessor(node);
        NodeType tmp = node->value;
        node->value = iop_node->value;
        iop_node->value = tmp;
        remove(iop_node);
    }
}

template <typename NodeType>
BinaryTreeNode<NodeType>*& BinarySearchTree<NodeType>::inorder_predecessor(BinaryTreeNode<NodeType>*& node)
{
    BinaryTreeNode<NodeType>** iop_node = &(node->left);
    while ((*iop_node)->right) {
        iop_node = &(*iop_node)->right;
    }
    return *iop_node;
}

template <typename NodeType>
void BinarySearchTree<NodeType>::build_balanced(const int* p, const int* r, BinaryTreeNode<NodeType>** node)
{
    if (p > r) {
        return;
    }
    const int* q = p + (r - p) / 2;
    *node = new BinaryTreeNode<NodeType>{*q};
    build_balanced(p, q - 1, &(*node)->left);
    build_balanced(q + 1, r, &(*node)->right);
}

}  // namespace Ps::Algo
