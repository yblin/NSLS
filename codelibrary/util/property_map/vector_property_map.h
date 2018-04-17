//
// Copyright 2015 Yangbin Lin. All Rights Reserved.
//
// Author: yblin.xmu@qq.com (Yangbin Lin)
//
// This file is part of the Code Library.
//

#ifndef UTIL_PROPERTY_MAP_VECTOR_PROPERTY_MAP_H_
#define UTIL_PROPERTY_MAP_VECTOR_PROPERTY_MAP_H_

#include <algorithm>
#include <vector>

#include "codelibrary/base/macros.h"

namespace cl {

/**
 * Interface of vector property map, used to represented various templated
 * vector property maps.
 */
class BaseVectorPropertyMap {
public:
    /// Default constructor
    BaseVectorPropertyMap() {}

    /// Destructor.
    virtual ~BaseVectorPropertyMap() {}

    /// Extend the number of elements by one.
    virtual void push_back() = 0;

    /// Remove the last element.
    virtual void pop_back() = 0;

    /// Swap two elements.
    virtual void swap(int id1, int id2) = 0;

    /// Return the number of elements.
    virtual int size() const = 0;

    /// Resize the data
    virtual void resize(int n) = 0;

    /// Clear the data.
    virtual void clear() = 0;
};

/// Vector Property Map.
template <typename T>
class VectorPropertyMap : public BaseVectorPropertyMap {
    typedef typename std::vector<T>::reference Reference;
    typedef typename std::vector<T>::const_reference ConstReference;

public:
    VectorPropertyMap(int size, const T& value = T())
        : size_(size), data_(size, value) {
        assert(size >= 0);
    }

    virtual ~VectorPropertyMap() {}

    Reference operator[] (int i) {
        return data_[i];
    }

    ConstReference operator[] (int i) const {
        return data_[i];
    }

    /**
     * @return the number of elements.
     */
    virtual int size() const {
        return size_;
    }

    const std::vector<T>& data() const { return data_; }

protected:
    /**
     * Extend the number of elements by one.
     */
    virtual void push_back() {
        ++size_;
        data_.push_back(T());
    }

    /**
     * Remove the last element.
     */
    virtual void pop_back() {
        assert(size_ > 0);

        --size_;
        data_.pop_back();
    }

    /**
     * Swap two elements.
     */
    virtual void swap(int id1, int id2) {
        std::swap(data_[id1], data_[id2]);
    }

    /**
     * Clear the data.
     */
    virtual void clear() {
        size_ = 0;
        data_.clear();
    }

    /**
     * Resize the data.
     */
    virtual void resize(int n) {
        assert(n >= 0);

        size_ = n;
        data_.resize(n);
    }

    int size_;
    std::vector<T> data_;

    DISALLOW_COPY_AND_ASSIGN(VectorPropertyMap);
};

} // namespace cl

#endif // UTIL_PROPERTY_MAP_VECTOR_PROPERTY_MAP_H_
