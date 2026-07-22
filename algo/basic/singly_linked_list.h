#pragma once

#include "utils/class_helper.h"

#include <cstddef>
#include <vector>

namespace ps::algo {

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
    uint32_t count_nodes() const;

    /// @brief convert the first num_elements of the linked list to a vector
    /// @return a vector containing the values of the linked list nodes
    std::vector<int> to_vector(int32_t num_elements = 10) const;

    /// @brief insert a node with value in front of the list
    Node* insert(int value);

    Node* insert_after(Node* node, int value);
    void insert_after(Node* node, Node* new_node);

    /// @brief merge two sorted linked lists into one sorted linked list
    /// @details the other list will be empty after the merge
    void merge(SinglyLinkedList& other);

    /// @brief reverse the linked list
    /// @details the head of the list will be updated to the new head after the reverse
    /// @note this is an in-place reverse, no new nodes are created
    void reverse();

    bool operator==(const SinglyLinkedList& rhs) const;

private:
    Node* head_;
};

} // namespace ps::algo
