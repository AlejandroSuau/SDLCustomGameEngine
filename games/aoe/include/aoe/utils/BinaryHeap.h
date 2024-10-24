#pragma once

#include <functional>
#include <vector>
#include <stdexcept>

template<typename T, typename Comparator = std::less<T>>
class BinaryHeap {
public:
    BinaryHeap() = default;

    void Push(T item);
    void Update(std::size_t index, bool sort_up);
    T& Top();
    const T& Top() const;
    void Pop();
    std::size_t Size() const;
    bool Empty() const;

private:
    struct BinaryHeapElement {
        std::size_t index;
        T element;
    };

    Comparator comparator_;
    std::vector<BinaryHeapElement> elements_;

    void HeapifyUp(BinaryHeapElement& element);
    void HeapifyDown(BinaryHeapElement& element);
    void Swap(BinaryHeapElement& element_left, BinaryHeapElement& element_right);

    std::size_t GetParentIndex(std::size_t index) const;
    std::size_t GetChildIndexLeft(std::size_t index) const;
    std::size_t GetChildIndexRight(std::size_t index) const;
};

template<typename T, typename Comparator>
void BinaryHeap<T, Comparator>::Push(T item) {
    elements_.emplace_back(elements_.size(), item);
    HeapifyUp(elements_.back());
}

template<typename T, typename Comparator>
void BinaryHeap<T, Comparator>::Update(std::size_t index, bool heapify_up) {
    if (heapify_up) {
        HeapifyUp(index);
    } else {
        HeapifyDown(index);
    }
}

template<typename T, typename Comparator>
T& BinaryHeap<T, Comparator>::Top() {
    if (elements_.empty()) throw std::out_of_range("Heap is empty");
    return elements_[0].element;
}

template<typename T, typename Comparator>
const T& BinaryHeap<T, Comparator>::Top() const {
    if (elements_.empty()) throw std::out_of_range("Heap is empty");
    return elements_[0].element;
}

template<typename T, typename Comparator>
void BinaryHeap<T, Comparator>::Pop() {
    if (elements_.empty()) throw std::out_of_range("Heap is empty");
    
    Swap(elements_[0], elements_.back());
    elements_.pop_back();
    if (!elements_.empty()) {
        HeapifyDown(elements_[0]);
    }
}

template<typename T, typename Comparator>
std::size_t BinaryHeap<T, Comparator>::Size() const {
    return elements_.size();
}

template<typename T, typename Comparator>
void BinaryHeap<T, Comparator>::HeapifyUp(BinaryHeapElement& element) {
    auto i = element.index;
    while (i != 0 && comparator_(elements_[GetParentIndex(i)].element, elements_[i].element)) {
        Swap(elements_[i], elements_[GetParentIndex(i)]);
        i = GetParentIndex(i);
    }
}

template<typename T, typename Comparator>
void BinaryHeap<T, Comparator>::HeapifyDown(BinaryHeapElement& element) {
    std::size_t i = element.index;
    while (true) {
        const auto index_l = GetChildIndexLeft(i);
        const auto index_r = GetChildIndexRight(i);
        auto smallest_index = i;

        if (index_l < elements_.size() && 
            comparator_(elements_[index_l].element, elements_[smallest_index].element)) {
            smallest_index = index_l;
        }

        if (index_r < elements_.size() &&
            comparator_(elements_[index_r].element, elements_[smallest_index].element)) {
            smallest_index = index_r;
        }

        if (smallest_index == i) break;

        Swap(elements_[i], elements_[smallest_index]);
        i = smallest_index;
    }
}

template<typename T, typename Comparator>
void BinaryHeap<T, Comparator>::Swap(BinaryHeapElement& element_left, BinaryHeapElement& element_right) {
    std::swap(element_left, element_right);
    element_left.index = elements_[element_left.index].index;
    element_right.index = elements_[element_right.index].index;
}

template<typename T, typename Comparator>
std::size_t BinaryHeap<T, Comparator>::GetParentIndex(std::size_t index) const {
    if (index == 0) throw std::out_of_range("Index 0 doesn't have a parent");
    return ((index - 1) / 2);
}

template<typename T, typename Comparator>
std::size_t BinaryHeap<T, Comparator>::GetChildIndexLeft(std::size_t index) const {
    return (2 * index + 1);
}

template<typename T, typename Comparator>
std::size_t BinaryHeap<T, Comparator>::GetChildIndexRight(std::size_t index) const {
    return (2 * index + 2);
}

template<typename T, typename Comparator>
bool BinaryHeap<T, Comparator>::Empty() const {
    return elements_.empty();
}