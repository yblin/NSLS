//
// Copyright 2014 Yangbin Lin. All Rights Reserved.
//
// Author: yblin.xmu@qq.com (Yangbin Lin)
//
// This file is part of the Code Library.
//

#ifndef UTIL_LIST_INPLACE_LIST_H_
#define UTIL_LIST_INPLACE_LIST_H_

#include <cassert>
#include <iterator>
#include <vector>

#include "codelibrary/base/macros.h"

namespace cl {

/// Inplace List.
/**
 * InplaceList arranges the data as a bidirectional list and allows constant
 * time insertion and deletion operations.
 *
 * Different from the STL list, InplaceList does not hold any object, it means
 * InplaceLlist dose not copy items during the insertion, and it does not free
 * the memory of items during the removal too.
 *
 * @parameter Node must have members: 'next()', 'prev()', 'set_next()', and
 *            'set_prev()'.
 */
template <class Node>
class InplaceList {
public:
    /// Iterator for InplaceList.
    class Iterator : public std::iterator<std::bidirectional_iterator_tag,
                                          Node> {
    public:
        Iterator() : node_(NULL) {}
        explicit Iterator(Node* node) : node_(node) {}

        bool operator == (const Iterator& rhs) const {
            return node_ == rhs.node_;
        }

        bool operator != (const Iterator& rhs) const {
            return node_ != rhs.node_;
        }

        Node& operator*()  const { return *node_; }
        Node* operator->() const { return  node_; }

        Iterator& operator++() {
            node_ = node_->next();
            return *this;
        }

        Iterator operator++(int /*n*/) {
            Iterator tmp = *this;
            ++*this;
            return tmp;
        }

        Iterator& operator--() {
            node_ = node_->prev();
            return *this;
        }

        Iterator  operator--(int /*n*/) {
            Iterator tmp = *this;
            --*this;
            return tmp;
        }

    protected:
        Node* node_;
    };

    /// Const iterator for InplaceList.
    class ConstIterator : public std::iterator<std::bidirectional_iterator_tag,
                                               const Node> {
    public:
        ConstIterator() : node_(NULL) {}
        explicit ConstIterator(Iterator i) : node_(&*i) {}
        explicit ConstIterator(const Node* node) : node_(node) {}

        bool operator == (const ConstIterator& rhs) const {
            return node_ == rhs.node_;
        }

        bool operator != (const ConstIterator& rhs) const {
            return node_ != rhs.node_;
        }

        const Node& operator * () const { return *node_; }
        const Node* operator ->() const { return  node_; }

        ConstIterator& operator++() {
            node_ = node_->next();
            return *this;
        }

        ConstIterator operator++(int /*n*/) {
            ConstIterator tmp = *this;
            ++*this;
            return tmp;
        }

        ConstIterator& operator--() {
            node_ = node_->prev();
            return *this;
        }

        ConstIterator  operator--(int /*n*/) {
            ConstIterator tmp = *this;
            --*this;
            return tmp;
        }

    protected:
        const Node* node_;
    };

    typedef std::reverse_iterator<Iterator>      ReverseIterator;
    typedef std::reverse_iterator<ConstIterator> ConstReverseIterator;

    InplaceList()
        : size_(0) {
        head_.set_next(&head_);
        head_.set_prev(&head_);
    }

    Iterator begin()                    { return Iterator(head_.next());       }
    Iterator end()                      { return Iterator(&head_);             }
    ConstIterator begin()         const { return ConstIterator(head_.next());  }
    ConstIterator end()           const { return ConstIterator(&head_);        }

    ReverseIterator rbegin() {
        return ReverseIterator(Iterator(head_.prev()));
    }

    ReverseIterator rend() {
        return ReverseIterator(Iterator(&head_));
    }

    ConstReverseIterator rbegin() const {
        return ConstReverseIterator(ConstIterator(head_.prev()));
    }

    ConstReverseIterator rend() const {
        return ConstReverseIterator(ConstIterator(&head_));
    }

    /**
     * Check if the list is empty.
     */
    bool empty() const {
        return size_ == 0;
    }

    /**
     * @return the number of elements in the list.
     */
    int size() const {
        return size_;
    }

    /**
     * Insert an element after the given iterator.
     */
    void Insert(Iterator i, Node* e) {
        Node* node = i.operator ->();
        e->set_next(node);
        e->set_prev(node->prev());
        node->prev()->set_next(e);
        node->set_prev(e);
        ++size_;
    }

    /**
     * Push back a node into node list.
     */
    void push_back(Node* e) {
        e->set_next(&head_);
        e->set_prev(head_.prev());
        head_.prev()->set_next(e);
        head_.set_prev(e);
        ++size_;
    }

    /**
     * Erase the node from node list.
     */
    void erase(Iterator e) {
        assert(size_ > 0);

        e->prev()->set_next(e->next());
        e->next()->set_prev(e->prev());

        --size_;
    }

    /**
     * Clear all nodes.
     */
    void clear() {
        size_ = 0;
        // We don't hold the actual object, so just reset the head pointer.
        head_.next = &head_;
        head_.prev = &head_;
    }

protected:
    int size_;  // The number of nodes in the list.
    Node head_; // The head of node list.

private:
    DISALLOW_COPY_AND_ASSIGN(InplaceList);
};

} // namespace cl

#endif // UTIL_LIST_INPLACE_LIST_H_
