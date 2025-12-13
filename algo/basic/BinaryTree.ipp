#pragma once

#include "BinaryTree.h"

#include <istream>
#include <ostream>
#include <stack>

namespace Ps::Algo {

template <typename NodeType>
std::vector<int> BinaryTree<NodeType>::inorder() const
{
    std::vector<int> elements;
    inorder(root_, elements);
    return elements;
}

template <typename NodeType>
std::vector<int> BinaryTree<NodeType>::inorder_non_rec() const
{
    std::vector<int> result;

    std::stack<BinaryTreeNode<NodeType>*> node_stack;
    BinaryTreeNode<NodeType>* node = root_;

    while (!node_stack.empty() || node) {
        if (node) {
            node_stack.push(node);
            node = node->left;
        }
        else {
            node = node_stack.top();
            node_stack.pop();
            result.push_back(node->value);
            node = node->right;
        }
    }

    return result;
}

template <typename NodeType>
std::vector<int> BinaryTree<NodeType>::preorder() const
{
    std::vector<int> elements;
    preorder(root_, elements);
    return elements;
}

template <typename NodeType>
bool BinaryTree<NodeType>::is_balanced() const
{
    if (!root_) {
        return true;
    }

    return std::abs(height(root_->left) - height(root_->right)) <= 1;
}

template <typename NodeType>
bool BinaryTree<NodeType>::is_symmetric() const
{
    if (!root_) {
        return true;
    }

    return is_symmetric(root_->left, root_->right);
}

template <typename NodeType>
std::pair<size_t, unsigned int> BinaryTree<NodeType>::max_in_level(const std::function<bool(int)>& pred) const
{
    std::vector<unsigned int> n_in_level;
    count_by_level(root_, pred, 0, n_in_level);

    std::pair<size_t, unsigned int> retval;

    for (size_t i = 0; i < n_in_level.size(); ++i) {
        if (n_in_level[i] > retval.second) {
            retval.first = i;
            retval.second = n_in_level[i];
        }
    }

    return retval;
}

template <typename NodeType>
std::pair<bool, int> BinaryTree<NodeType>::least_common_ancestor(int a, int b) const
{
    BinaryTreeNode<NodeType>* lca_node = least_common_ancestor(root_, a, b);
    if (lca_node) {
        return std::pair<bool, int>{true, lca_node->value};
    }
    else {
        return std::pair<bool, int>{false, 0};
    }
}

template <typename NodeType>
int BinaryTree<NodeType>::height(const BinaryTreeNode<NodeType>* node) const
{
    if (!node) {
        return -1;
    }

    return 1 + std::max(height(node->left), height(node->right));
}

template <typename NodeType>
void BinaryTree<NodeType>::inorder(BinaryTreeNode<NodeType>* node, std::vector<int>& elements) const
{
    if (!node) {
        return;
    }

    inorder(node->left, elements);
    elements.push_back(node->value);
    inorder(node->right, elements);
}

template <typename NodeType>
void BinaryTree<NodeType>::preorder(BinaryTreeNode<NodeType>* node, std::vector<int>& elements) const
{
    if (!node) {
        return;
    }

    elements.push_back(node->value);
    preorder(node->left, elements);
    preorder(node->right, elements);
}

template <typename NodeType>
bool BinaryTree<NodeType>::is_symmetric(const BinaryTreeNode<NodeType>* lnode,
                                        const BinaryTreeNode<NodeType>* rnode) const
{
    if (!lnode && !rnode) {
        return true;
    }
    else if (lnode && rnode) {
        return (lnode->value == rnode->value) && is_symmetric(lnode->left, rnode->right) &&
               is_symmetric(lnode->right, rnode->left);
    }
    else {
        return false;
    }
}

template <typename NodeType>
void BinaryTree<NodeType>::count_by_level(BinaryTreeNode<NodeType>* node,
                                          const std::function<bool(int)>& pred,
                                          unsigned int level,
                                          std::vector<unsigned int>& nvalues_in_level) const
{
    if (!node) {
        return;
    }

    if (level == nvalues_in_level.size()) {
        nvalues_in_level.push_back(0);
    }

    if (pred(node->value)) {
        ++nvalues_in_level[level];
    }

    count_by_level(node->left, pred, level + 1, nvalues_in_level);
    count_by_level(node->right, pred, level + 1, nvalues_in_level);
}

template <typename NodeType>
BinaryTreeNode<NodeType>* BinaryTree<NodeType>::least_common_ancestor(BinaryTreeNode<NodeType>* node,
                                                                      int a,
                                                                      int b) const
{
    if (!node) {
        return nullptr;
    }
    else if (a == node->value || b == node->value) {
        return node;
    }

    BinaryTreeNode<NodeType>* lnode = least_common_ancestor(node->left, a, b);
    BinaryTreeNode<NodeType>* rnode = least_common_ancestor(node->right, a, b);
    if (lnode && rnode) {
        return node;
    }
    return lnode ? lnode : rnode;
}

template <typename NodeType>
void BinaryTree<NodeType>::read(std::istream& input_stream, BinaryTreeNode<NodeType>*& node)
{
    static std::string str;

    std::getline(input_stream, str, ',');

    if (str == "N") {
        return;
    }

    bool intermediate = false;
    if (str[str.size() - 1] == 'i') {
        intermediate = true;
        str.pop_back();
    }

    node = new BinaryTreeNode<NodeType>{stoi(str)};

    if (intermediate) {
        read(input_stream, node->left);
        read(input_stream, node->right);
    }
}

template <typename NodeType>
void BinaryTree<NodeType>::write(const BinaryTreeNode<NodeType>* node, std::ostream& output_stream)
{
    if (!node) {
        output_stream << "N,";
        return;
    }
    output_stream << node->value;
    if (node->left || node->right) {
        output_stream << "i,";
        write(node->left, output_stream);
        write(node->right, output_stream);
    }
    else {
        output_stream << ',';
    }
}

template <typename NodeType>
void BinaryTree<NodeType>::delete_node_rec(BinaryTreeNode<NodeType>* node)
{
    if (node == nullptr) {
        return;
    }
    delete_node_rec(node->left);
    delete_node_rec(node->right);
    delete node;
}

}  // namespace Ps::Algo
