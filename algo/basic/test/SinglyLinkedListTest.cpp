#include "algo/basic/SinglyLinkedList.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("SinglyLinkedList Merge")
{
    Ps::Algo::SinglyLinkedList sll;
    sll.insert(9);
    sll.insert(7);
    sll.insert(5);
    sll.insert(3);
    sll.insert(1);

    Ps::Algo::SinglyLinkedList sll2;
    sll2.insert(8);
    sll2.insert(6);
    sll2.insert(4);
    sll2.insert(2);

    sll.merge(sll2);

    Ps::Algo::SinglyLinkedList expected;
    expected.insert(9);
    expected.insert(8);
    expected.insert(7);
    expected.insert(6);
    expected.insert(5);
    expected.insert(4);
    expected.insert(3);
    expected.insert(2);
    expected.insert(1);

    CHECK(sll == expected);
}

TEST_CASE("SinglyLinkedList Reverse")
{
    Ps::Algo::SinglyLinkedList sll;
    sll.insert(5);
    sll.insert(2);
    sll.insert(4);
    sll.insert(1);

    sll.reverse();

    Ps::Algo::SinglyLinkedList expected;
    expected.insert(1);
    expected.insert(4);
    expected.insert(2);
    expected.insert(5);

    CHECK(sll == expected);
}
