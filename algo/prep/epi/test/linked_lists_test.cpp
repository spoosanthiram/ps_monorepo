#include "algo/prep/epi/linked_lists.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("linked_lists has_cycle")
{
    ps::algo::SinglyLinkedList sll;
    auto head = sll.insert(7);
    auto node10 = sll.insert_after(head, 10);
    auto node18 = sll.insert_after(node10, 18);
    auto node23 = sll.insert_after(node18, 23);
    auto node25 = sll.insert_after(node23, 25);
    auto node43 = sll.insert_after(node25, 43);

    // No cycle
    CHECK(ps::algo::has_cycle(head) == nullptr);

    // Create a cycle: 43 -> 18
    node43->next = node18;
    CHECK(ps::algo::has_cycle(head) == node18);

    // Fix the cycle
    node43->next = nullptr;

    // Create a cycle: 43 -> 23
    node43->next = node23;
    CHECK(ps::algo::has_cycle(head) == node23);

    // Fix the cycle, otherwise the destructor will go into an infinite loop
    node43->next = nullptr;
}

TEST_CASE("linked_lists overlapping_lists")
{
    ps::algo::SinglyLinkedList list1;
    auto head1 = list1.insert(7);
    auto node10 = list1.insert_after(head1, 10);
    auto node18 = list1.insert_after(node10, 18);
    auto node23 = list1.insert_after(node18, 23);
    auto node25 = list1.insert_after(node23, 25);
    list1.insert_after(node25, 43);

    ps::algo::SinglyLinkedList list2;
    auto head2 = list2.insert(5);
    auto node15 = list2.insert_after(head2, 15);

    // No overlap
    CHECK(ps::algo::overlapping_lists(list1, list2) == nullptr);

    // Create an overlap: 15 -> 18
    node15->next = node18;
    CHECK(ps::algo::overlapping_lists(list1, list2) == node18);

    // Fix the overlap
    node15->next = nullptr;

    // Create an overlap: 15 -> 23
    node15->next = node23;
    CHECK(ps::algo::overlapping_lists(list1, list2) == node23);

    // Fix the overlap, otherwise the destructor will go into an infinite loop
    node15->next = nullptr;
}
