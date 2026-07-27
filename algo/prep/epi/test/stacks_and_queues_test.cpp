#include "algo/prep/epi/stacks_and_queues.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("StackWithMax push, pop, max")
{
    ps::algo::StackWithMax stack;

    CHECK_THROWS_AS(stack.pop(), std::underflow_error);
    CHECK_THROWS_AS(stack.max(), std::underflow_error);

    stack.push(3); // 3
    CHECK(stack.max() == 3);

    stack.push(5); // 3, 5
    CHECK(stack.max() == 5);

    stack.push(2); // 3, 5, 2
    CHECK(stack.max() == 5);

    stack.push(1); // 3, 5, 2, 1
    CHECK(stack.max() == 5);

    stack.push(7); // 3, 5, 2, 1, 7
    CHECK(stack.max() == 7);

    CHECK(stack.pop() == 7); // 3, 5, 2, 1
    CHECK(stack.max() == 5);

    CHECK(stack.pop() == 1); // 3, 5, 2
    CHECK(stack.max() == 5);

    CHECK(stack.pop() == 2); // 3, 5
    CHECK(stack.max() == 5);

    CHECK(stack.pop() == 5); // 3
    CHECK(stack.max() == 3);

    CHECK(stack.pop() == 3);
}

TEST_CASE("is_well_formed")
{
    CHECK(ps::algo::is_well_formed("{}"));
    CHECK(ps::algo::is_well_formed("()"));
    CHECK(ps::algo::is_well_formed("[]"));
    CHECK(ps::algo::is_well_formed("{[()]}"));
    CHECK(ps::algo::is_well_formed("{[()]}[]{}"));

    CHECK_FALSE(ps::algo::is_well_formed("{"));
    CHECK_FALSE(ps::algo::is_well_formed("}"));
    CHECK_FALSE(ps::algo::is_well_formed("("));
    CHECK_FALSE(ps::algo::is_well_formed(")"));
    CHECK_FALSE(ps::algo::is_well_formed("["));
    CHECK_FALSE(ps::algo::is_well_formed("]"));
    CHECK_FALSE(ps::algo::is_well_formed("{[}]"));
    CHECK_FALSE(ps::algo::is_well_formed("{[(])}"));
}
