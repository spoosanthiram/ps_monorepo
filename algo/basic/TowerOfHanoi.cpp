#include "TowerOfHanoi.h"

#include <iostream>

namespace Ps::Algo {

void Stack::print() const
{
    std::cout << name_ << ": ";
    for (const auto val : stack_) {
        std::cout << val << ", ";
    }
    std::cout << '\n';
}

TowerOfHanoi::TowerOfHanoi(uint32_t size)
    : source_{"Source"}
    , inter_{"Inter"}
    , dest_{"Dest"}
{
    for (; size > 0; --size) {
        source_.push(size);
    }
}

void TowerOfHanoi::print() const
{
    source_.print();
    inter_.print();
    dest_.print();
    std::cout << '\n';
}

void TowerOfHanoi::solve()
{
    solve(0, source_, inter_, dest_);
}

void TowerOfHanoi::solve(size_t index, Stack& source, Stack& inter, Stack& dest)
{
    if (index == source.size()) {
        return;
    }
    else if (index + 1 == source.size()) {
        auto val = source.top();
        source.pop();
        dest.push(val);
        print();
        return;
    }

    auto inter_size = inter.size();

    solve(index + 1, source, dest, inter); // sub1
    {
        auto val = source.top();
        source.pop();
        dest.push(val);
        print();
    }
    solve(inter_size, inter, source, dest); // sub2
}

} // namespace Ps::Algo
