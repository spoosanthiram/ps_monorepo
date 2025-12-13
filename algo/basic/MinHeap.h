#pragma once

#include <format>
#include <functional>
#include <stdexcept>

namespace Ps::Algo {

template <typename T>
struct NullIndex
{
    NullIndex() = default;
    NullIndex(const NullIndex& other) = default;
    void operator()(const T&, size_t) {}
};

/// MinHeap class abstracts the min heap data structure.
//
template <typename T, typename LessThan = std::less<T>, typename Index = NullIndex<T>>
class MinHeap
{
public:
    MinHeap() = default;
    MinHeap(const std::vector<T>& elements)
        : heap_{elements}
    {
        make();
    }
    MinHeap(std::vector<T>&& elements)
        : heap_{elements}
    {
        make();
    }
    MinHeap(LessThan lt, Index index)
        : less_than_{lt}
        , index_{index}
    {}
    MinHeap(const std::vector<T>& elements, LessThan lt, Index index)
        : heap_{elements}
        , less_than_{lt}
        , index_{index}
    {
        make();
    }
    MinHeap(std::vector<T>&& elements, LessThan lt, Index index)
        : heap_{elements}
        , less_than_{lt}
        , index_{index}
    {
        make();
    }

    size_t size() const { return heap_.size(); }
    const T& top() const { return heap_.front(); }
    bool is_empty() const { return heap_.empty(); }

    void sift_down(size_t i);
    void sift_up(size_t i);

    void push(const T& element)
    {
        auto i = heap_.size();
        index_(element, i);
        heap_.push_back(element);

        sift_up(i);
    }

    T pop()
    {
        if (heap_.empty()) {
            throw std::underflow_error{"There is no more elements in the heap"};
        }

        auto element = heap_[0];

        heap_[0] = heap_.back();
        index_(heap_[0], 0);
        heap_.pop_back();

        sift_down(0);

        return element;
    }

private:
    void make();

    size_t parent(size_t i) { return (i - 1) / 2; }
    size_t left(size_t i) { return 2 * i + 1; }
    size_t right(size_t i) { return 2 * i + 2; }

private:
    std::vector<T> heap_;
    LessThan less_than_;
    Index index_;
};

template <typename T, typename LessThan, typename Index>
void MinHeap<T, LessThan, Index>::make()
{
    for (size_t i = 0; i < heap_.size(); ++i) {
        index_(heap_[i], i);
    }

    for (int64_t i = heap_.size() / 2 - 1; i >= 0; --i) {
        sift_down(i);
    }
}

template <typename T, typename LessThan, typename Index>
void MinHeap<T, LessThan, Index>::sift_down(size_t i)
{
    size_t l = left(i);
    size_t r = right(i);
    size_t smallest = i;

    if (l < heap_.size() && less_than_(heap_[l], heap_[i])) {
        smallest = l;
    }
    if (r < heap_.size() && less_than_(heap_[r], heap_[smallest])) {
        smallest = r;
    }

    if (smallest != i) {
        std::swap(heap_[i], heap_[smallest]);
        index_(heap_[i], i);
        index_(heap_[smallest], smallest);
        sift_down(smallest);
    }
}

template <typename T, typename LessThan, typename Index>
void MinHeap<T, LessThan, Index>::sift_up(size_t i)
{
    if (i >= heap_.size()) {
        throw std::runtime_error(
            std::format("The index for MinHeap<>::siftup() is not within the range [{}, {}]", 0, heap_.size() - 1));
    }

    while (i > 0 && less_than_(heap_[i], heap_[parent(i)])) {
        std::swap(heap_[i], heap_[parent(i)]);
        index_(heap_[i], i);
        index_(heap_[parent(i)], parent(i));
        i = parent(i);
    }
}

} // namespace Ps::Algo
