#include "algo/prep/CircularQueue.h"

#include <iostream>

namespace Ps::Algo {

void CircularQueue::enqueue(int val)
{
    if (size_ == capacity_) {
        std::unique_lock lck{mutex_};
        cv_.wait(lck, [this]() { return size_ < capacity_;});
    }
    {
        std::lock_guard lg{mutex_};
        buffer_[(index_ + size_) % capacity_] = val;
        ++size_;
    }
    cv_.notify_all();
}

int CircularQueue::dequeue() {
    if (size_ == 0){
        std::unique_lock lck{mutex_};
        cv_.wait(lck, [this]() { return size_ > 0; });
    }
    int retval = 0;
    {
        std::lock_guard lg{mutex_};
        retval = buffer_[index_];
        index_ = (index_ + 1) % capacity_;
        --size_;
    }
    cv_.notify_all();
    return retval;
}

} // namespace Ps::Algo
