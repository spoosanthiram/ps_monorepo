#include "linked_lists.h"

namespace ps::algo {

SinglyLinkedList::Node* has_cycle(SinglyLinkedList::Node* head)
{
    bool cycle_detected = false;

    SinglyLinkedList::Node* slow = head;
    SinglyLinkedList::Node* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            cycle_detected = true;
            break;
        }
    }

    if (cycle_detected) {
        slow = head;
        while (slow != fast) {
            slow = slow->next;
            fast = fast->next;
        }
        return slow;
    }

    return nullptr;
}

void advance_list_by_k(const SinglyLinkedList::Node*& node, uint32_t k)
{
    while (k > 0 && node) {
        node = node->next;
        --k;
    }
}

const SinglyLinkedList::Node* overlapping_lists(const SinglyLinkedList& list1, const SinglyLinkedList& list2)
{
    if (!list1.chead() || !list2.chead()) {
        return nullptr;
    }

    auto head1 = list1.chead();
    auto head2 = list2.chead();

    const auto len1 = list1.count_nodes();
    const auto len2 = list2.count_nodes();

    // Advance the longer list by the difference in lengths
    advance_list_by_k(len1 > len2 ? head1 : head2, std::abs(static_cast<int32_t>(len1) - static_cast<int32_t>(len2)));

    // Traverse both lists together to find the overlap point
    while (head1 && head2) {
        if (head1 == head2) {
            return head1; // Overlap found
        }
        head1 = head1->next;
        head2 = head2->next;
    }

    return nullptr; // No overlap
}

} // namespace ps::algo
