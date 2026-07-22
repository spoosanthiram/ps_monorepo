#pragma once

#include "algo/basic/singly_linked_list.h"

namespace ps::algo {

/// EPI 8.1: Merge two sorted linked lists, refer to the implementation of SinglyLinkedList::merge

/// EPI 8.2: Reverse a linked list, refer to the implementation of SinglyLinkedList::reverse

/// @brief EPI 8.3: Test for Cycle in a singly linked list
/// @param head pointer to the head of the linked list
/// @return nullptr if no cycle, else pointer to the node where the cycle begins
SinglyLinkedList::Node* has_cycle(SinglyLinkedList::Node* head);

/// @brief EPI 8.4: Test for overlapping lists - lists are cycle-free
/// @param head1 pointer to the head of the first linked list
/// @param head2 pointer to the head of the second linked list
/// @return nullptr if no overlap, else pointer to the node where the overlap begins
const SinglyLinkedList::Node* overlapping_lists(const SinglyLinkedList& list1, const SinglyLinkedList& list2);

} // namespace ps::algo
