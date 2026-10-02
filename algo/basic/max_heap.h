#pragma once

#include <format>
#include <vector>

namespace ps::algo {

/// MaxHeap class abstracts the max heap data structure.
//
template <typename ElemType>
class MaxHeap
{
public:
    MaxHeap() = default;
    MaxHeap(const std::vector<ElemType>& elements)
        : heap_{elements}
    {
        make();
    }
    MaxHeap(std::vector<ElemType>&& elements)
        : heap_{elements}
    {
        make();
    }

    size_t size() const { return heap_.size(); }
    const ElemType& top() const { return heap_.front(); }
    bool is_empty() const { return heap_.empty(); }

    void push(const ElemType& element);
    ElemType pop();

    void heapify(size_t idx);
    void sift_up(size_t idx);

private:
    void make();

    size_t parent(size_t i) { return (i - 1) / 2; }
    size_t left(size_t i) { return 2 * i + 1; }
    size_t right(size_t i) { return 2 * i + 2; }

private:
    std::vector<ElemType> heap_;
};

template <typename ElemType>
void MaxHeap<ElemType>::push(const ElemType& element)
{
    const auto idx = heap_.size();
    heap_.push_back(element);
    sift_up(idx);
}

template <typename ElemType>
ElemType MaxHeap<ElemType>::pop()
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

template <typename ElemType>
void MaxHeap<ElemType>::heapify(size_t idx)
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

template <typename ElemType>
void MaxHeap<ElemType>::sift_up(size_t idx)
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

template <typename ElemType>
void MaxHeap<ElemType>::make()
{
    for (int64_t i = (heap_.size() / 2) - 1; i >= 0; --i) {
        heapify(i);
    }
}

} // namespace ps::algo
