#pragma once

#include <cstdint>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

namespace Ps::Algo {

class Stack
{
public:
    Stack(std::string_view name)
        : name_{name}
    {}

    size_t size() const { return stack_.size(); }
    bool is_empty() const { return stack_.empty(); }
    uint32_t top() const
    {
        if (stack_.empty()) {
            throw std::underflow_error{"Stack is empty"};
        }
        return stack_.back();
    }
    void print() const;

    bool operator==(const Stack& other) const { return stack_ == other.stack_; }

    void push(uint32_t val) { stack_.push_back(val); }
    void pop() { stack_.pop_back(); }

private:
    std::string name_;
    std::vector<uint32_t> stack_;
};

class TowerOfHanoi
{
public:
    TowerOfHanoi(uint32_t size);

    const Stack& source() const { return source_; }
    const Stack& intermediate() const { return inter_; }
    const Stack& destination() const { return dest_; }
    void print() const;

    void solve();

private:
    void solve(size_t index, Stack& source, Stack& inter, Stack& dest);

private:
    Stack source_;
    Stack inter_;
    Stack dest_;
};

} // namespace Ps::Algo
