#include "stacks_and_queues.h"

#include <stack>
#include <stdexcept>

namespace ps::algo {

void StackWithMax::push(int value)
{
    int current_max = stack_.empty() ? value : std::max(value, stack_.back().current_max);
    stack_.push_back({value, current_max});
}

int StackWithMax::pop()
{
    if (stack_.empty()) {
        throw std::underflow_error("Stack is empty");
    }
    int value = stack_.back().value;
    stack_.pop_back();
    return value;
}

int StackWithMax::max() const
{
    if (stack_.empty()) {
        throw std::underflow_error("Stack is empty");
    }
    return stack_.back().current_max;
}

char matching_bracket(char c)
{
    switch (c) {
        case '}':
            return '{';
        case ')':
            return '(';
        case ']':
            return '[';
        default:
            return '\0'; // Invalid character
    }
}

bool is_well_formed(const std::string_view str)
{
    std::stack<char> pbb_stack; // Parentheses, Braces, and Brackets stack
    for (char ch : str) {
        if ('(' == ch || '[' == ch || '{' == ch) {
            pbb_stack.push(ch);
        }
        else if (pbb_stack.empty() || matching_bracket(ch) != pbb_stack.top()) {
            return false;
        }
        else {
            pbb_stack.pop();
        }
    }
    return pbb_stack.empty();
}

} // namespace ps::algo
