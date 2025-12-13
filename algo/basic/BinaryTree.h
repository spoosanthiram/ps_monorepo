#pragma once

#include "core/utils/ClassHelper.h"

#include <functional>
#include <istream>
#include <ostream>
#include <vector>

namespace Ps::Algo {

template <typename NodeType>
struct BinaryTreeNode
{
    BinaryTreeNode(const NodeType& val)
        : value{val}
    {}
    NodeType value;
    BinaryTreeNode<NodeType>* left{nullptr};
    BinaryTreeNode<NodeType>* right{nullptr};
};

template <typename NodeType>
class BinaryTree
{
public:
    BinaryTree() = default;
    COPY_CONSTRUCTOR(BinaryTree) = delete;
    BinaryTree(BinaryTree&& rhs) // move constructor
    {
        root_ = rhs.root_;
        rhs.root_ = nullptr;
    }
    virtual ~BinaryTree() { delete_node_rec(root_); }

    COPY_ASSIGNMENT(BinaryTree) = delete;
    MOVE_ASSIGNMENT(BinaryTree) = delete;

    int height() const { return height(root_); }
    std::vector<int> inorder() const;
    std::vector<int> inorder_non_rec() const;
    std::vector<int> preorder() const;
    bool is_balanced() const;
    bool is_symmetric() const;
    std::pair<size_t, unsigned int> max_in_level(const std::function<bool(int)>& pred) const;
    std::pair<bool, int> least_common_ancestor(int a, int b) const;

    void read(std::istream& input_stream) { read(input_stream, root_); }
    void write(std::ostream& output_stream) { write(root_, output_stream); }

protected:
    BinaryTreeNode<NodeType>*& root() { return root_; }

private:
    int height(const BinaryTreeNode<NodeType>* node) const;
    void inorder(BinaryTreeNode<NodeType>* node, std::vector<int>& elements) const;
    void preorder(BinaryTreeNode<NodeType>* node, std::vector<int>& elements) const;
    bool is_symmetric(const BinaryTreeNode<NodeType>* lnode, const BinaryTreeNode<NodeType>* rnode) const;
    void count_by_level(BinaryTreeNode<NodeType>* node,
                        const std::function<bool(int)>& pred,
                        unsigned int level,
                        std::vector<unsigned int>& nvalues_in_level) const;
    BinaryTreeNode<NodeType>* least_common_ancestor(BinaryTreeNode<NodeType>* node, int a, int b) const;

    void read(std::istream& input_stream, BinaryTreeNode<NodeType>*& node);
    void write(const BinaryTreeNode<NodeType>* node, std::ostream& output_stream);

    void delete_node_rec(BinaryTreeNode<NodeType>* node);

private:
    BinaryTreeNode<NodeType>* root_{nullptr};
};

} // namespace Ps::Algo
