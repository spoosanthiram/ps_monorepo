#pragma once

#include "core/utils/ClassHelper.h"

#include <cstddef>

namespace Ps::Algo {

class SinglyLinkedList
{
public:
    struct Node
    {
        Node(int value)
            : data{value}
            , next{nullptr}
        {}
        int data;
        Node* next;
    };

public:
    SinglyLinkedList()
        : head_{nullptr}
    {}
    ~SinglyLinkedList();

    COPY_CONSTRUCTOR(SinglyLinkedList) = delete;
    MOVE_CONSTRUCTOR(SinglyLinkedList) = delete;
    COPY_ASSIGNMENT(SinglyLinkedList) = delete;
    MOVE_ASSIGNMENT(SinglyLinkedList) = delete;

    int front() const { return head_->data; }
    Node* head() { return head_; }
    const Node* chead() const { return head_; }

    /// @brief count the number of nodes aka size
    size_t count_nodes() const;

    /// @brief insert a node with value in front of the list
    void insert(int value);

    void insert_after(Node* node, int value);

    void merge(SinglyLinkedList& other);
    void reverse();

    bool operator==(const SinglyLinkedList& rhs) const;

private:
    Node* head_;
};

} // namespace Ps::Algo
