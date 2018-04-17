//
// Copyright 2011 Yangbin Lin. All Rights Reserved.
//
// Author: yblin.xmu@qq.com (Yangbin Lin)
//
// This file is part of the Code Library.
//

#ifndef UTIL_COMMON_SEQUENCE_H_
#define UTIL_COMMON_SEQUENCE_H_

#include <algorithm>
#include <cassert>
#include <functional>
#include <vector>

#include "codelibrary/base/macros.h"

namespace cl {

/// Sequence.
/**
 * Given a list, Sequence gives the positions in list at which each successive
 * element of std::sort(list) appears. The element in the original list dose not
 * change.
 *
 * Example:
 *    int a[] = {2, 3, 1}
 *    Sequence<int> seq(a + 0, a + 3);
 *    seq.orders(); // Equal to (2, 0, 1).
 */
template <typename T, typename Compare = std::less<T> >
class Sequence {
    /// Used to get the order by sorting.
    template <typename PointerType>
    struct Node {
        /**
         * Less operation, used for sort.
         */
        bool operator < (const Node& node) const {
            return compare(*pointer, *node.pointer);
        }

        int position;        // The position in the original array.
        PointerType pointer; // The pointer to the actual value.
        Compare compare;     // Used to compare.
    };

public:
    /**
     * Construct sequence from [first, last).
     */
    template <typename Iterator>
    Sequence(Iterator first, Iterator last) {
        size_ = std::distance(first, last);
        assert(size_ >= 0);

        std::vector<Node<Iterator> > nodes(size_);
        Iterator p = first;
        for (int i = 0; i < size_; ++i) {
            nodes[i].position = i;
            nodes[i].pointer = p++;
        }

        if (!std::is_sorted(nodes.begin(), nodes.end())) {
            std::sort(nodes.begin(), nodes.end());
        }

        orders_.resize(size_);
        for (int i = 0; i < size_; ++i) {
            orders_[i] = nodes[i].position;
        }
    }

    explicit Sequence(const std::vector<T>& values)
        : Sequence(values.begin(), values.end()) {}

    /**
     * Reverse the sequence.
     */
    void Reverse() {
        std::reverse(orders_.begin(), orders_.end());
    }

    int operator[] (int i) const {
        return orders_[i];
    }

    const std::vector<int>& orders() const { return orders_; }

    int size() const { return size_; }

private:
    int size_; // The size of the sequence.

    // The order of the original array.
    // The orders_[i] store the i-th smallest element's index in the original
    // array, where smallest is defined by the Compare in template argument.
    std::vector<int> orders_;

    DISALLOW_COPY_AND_ASSIGN(Sequence);
};

} // namespace cl

#endif // UTIL_COMMON_SEQUENCE_H_
