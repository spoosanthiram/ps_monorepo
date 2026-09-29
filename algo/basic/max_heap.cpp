#include "max_heap.h"

#include <format>

namespace ps::algo {

void MaxHeap::push(int element)
{
    const auto idx = heap_.size();
    heap_.push_back(element);
    sift_up(idx);
}

int MaxHeap::pop()
{
    if (heap_.empty()) {
        throw std::underflow_error{"There is no more elements in the heap"};
    }

    const auto element = heap_[0];

    heap_[0] = heap_.back();
    heap_.pop_back();

    heapify(0);

    return element;
}

void MaxHeap::heapify(size_t idx)
{
    size_t left_idx = left(idx);
    size_t right_idx = right(idx);
    size_t largest = idx;

    if (left_idx < heap_.size() && heap_[left_idx] > heap_[largest]) {
        largest = left_idx;
    }
    if (right_idx < heap_.size() && heap_[right_idx] > heap_[largest]) {
        largest = right_idx;
    }

    if (largest != idx) {
        std::swap(heap_[idx], heap_[largest]);
        heapify(largest);
    }
}

void MaxHeap::sift_up(size_t idx)
{
    if (idx >= heap_.size()) {
        throw std::runtime_error(
            std::format("The index for MaxHeap<>::siftup() is not within the range [{}, {}]", 0, heap_.size() - 1));
    }

    while (idx > 0 && heap_[idx] > heap_[parent(idx)]) {
        std::swap(heap_[idx], heap_[parent(idx)]);
        idx = parent(idx);
    }
}

void MaxHeap::make()
{
    for (int64_t i = (heap_.size() / 2) - 1; i >= 0; --i) {
        heapify(i);
    }
}

} // namespace ps::algo
