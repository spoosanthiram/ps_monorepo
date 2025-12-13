#include "algo/prep/CircularBuffer.h"

#include <format>
#include <iostream>

namespace Ps::Algo {

void CircularBuffer::push_back(int val)
{
    buffer_[(head_ + size_) % capacity_] = val;
    if (size_ == capacity_) {
        head_ = (head_ + 1) % capacity_;
    }
    else {
        ++size_;
    }
}

int CircularBuffer::at(uint32_t index) const
{
    if (index >= size_) {
        throw std::out_of_range{"Index outside the size"};
    }
    return buffer_[(head_ + index) % capacity_];
}

int CircularBuffer::pop_back()
{
    if (size_ == 0) {
        throw std::underflow_error{"Buffer is empty"};
    }
    --size_;
    return buffer_[(head_ + size_) % capacity_];
}

void CircularBuffer::print() const
{
    std::cout << std::format("head: {}, size: {}", head_, size_) << '\n';
    for (uint32_t i = 0; i < size_; ++i) {
        std::cout << at(i) << ", ";
    }
    std::cout << "\n";
}

} // namespace Ps::Algo
