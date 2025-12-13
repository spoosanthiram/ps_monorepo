#pragma once

#include <condition_variable>
#include <mutex>
#include <vector>

namespace Ps::Algo {

class CircularQueue
{
public:
    CircularQueue(uint32_t capacity)
        : capacity_{capacity}
    {
        buffer_ = new int[capacity_];
    }
    ~CircularQueue() { delete[] buffer_; }

    uint32_t size() const { return size_; }

    void enqueue(int val);
    int dequeue();

private:
    int* buffer_;
    uint32_t capacity_;
    uint32_t index_ = 0;
    uint32_t size_ = 0;

    std::mutex mutex_;
    std::condition_variable cv_;
};

} // namespace Ps::Algo
