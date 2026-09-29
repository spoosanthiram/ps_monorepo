#pragma once

#include <vector>

namespace ps::algo {

/// MaxHeap class abstracts the max heap data structure.
//
class MaxHeap
{
public:
    MaxHeap() = default;
    MaxHeap(const std::vector<int>& elements)
        : heap_{elements}
    {
        make();
    }
    MaxHeap(std::vector<int>&& elements)
        : heap_{elements}
    {
        make();
    }

    size_t size() const { return heap_.size(); }
    int top() const { return heap_.front(); }
    bool is_empty() const { return heap_.empty(); }

    void push(int element);
    int pop();

    void heapify(size_t idx);
    void sift_up(size_t idx);

private:
    void make();

    size_t parent(size_t i) { return (i - 1) / 2; }
    size_t left(size_t i) { return 2 * i + 1; }
    size_t right(size_t i) { return 2 * i + 2; }

private:
    std::vector<int> heap_;
};

} // namespace ps::algo
