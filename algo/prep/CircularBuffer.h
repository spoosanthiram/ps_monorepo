#pragma once

#include <cstdint>

namespace Ps::Algo {

class CircularBuffer
{
public:
    CircularBuffer(uint32_t capacity)
        : capacity_{capacity}
    {
        buffer_ = new int[capacity_];
    }
    ~CircularBuffer() { delete[] buffer_; }

    void push_back(int val);
    int at(uint32_t index) const;
    int pop_back();
    void resize(uint32_t new_capacity);

    void print() const;

private:
    int* buffer_;
    uint32_t head_{0};
    uint32_t size_{0};
    uint32_t capacity_;
};

} // namespace Ps::Algo
