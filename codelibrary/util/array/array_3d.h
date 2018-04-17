//
// Copyright 2013 Yangbin Lin. All Rights Reserved.
//
// Author: yblin.xmu@qq.com (Yangbin Lin)
//
// This file is part of the Code Library.
//

#ifndef UTIL_ARRAY_ARRAY_3D_H_
#define UTIL_ARRAY_ARRAY_3D_H_

#include <algorithm>
#include <cassert>
#include <limits>
#include <vector>

namespace cl {

/// 3D Array.
/**
 * This class is as most efficient as C-style 3d array.
 * User can access the data of Array3D by () operator.
 */
template<typename T>
class Array3D {
    typedef typename std::vector<T>::reference       Reference;
    typedef typename std::vector<T>::const_reference ConstReference;

public:
    typedef typename std::vector<T>::iterator Iterator;
    typedef typename std::vector<T>::const_iterator ConstIterator;
    typedef typename std::vector<T>::reverse_iterator ReverseIterator;
    typedef typename std::vector<T>::const_reverse_iterator
                     ConstReverseIterator;

    Array3D()
        : size1_(0), size2_(0), size3_(0), size_(0), size23_(0) {}

    Array3D(int size1, int size2, int size3, const T& value = T())
        : size1_(size1), size2_(size2), size3_(size3) {
        assert(CheckDimension(size1, size2, size3));

        size23_ = size2_ * size3_;
        size_ = size1_ * size2_ * size3_;
        data_.resize(size_, value);
    }

    /**
     * Clear the data of 2d array and set rows and columns to zero.
     */
    void clear() {
        std::vector<T>().swap(data_);  // Clear the data by swap trick.
        size_ = 0;
        size1_ = 0;
        size2_ = 0;
        size3_ = 0;
        size23_ = 0;
    }

    /**
     * Resize the 3d array.
     *
     * @param size1 - the size of first dimension after resize.
     * @param size2 - the size of second dimension after resize.
     * @param size3 - the size of third dimension after resize.
     * @param value - the default value to fill the extra 3d array data.
     */
    void Resize(int size1, int size2, int size3, const T& value = T()) {
        assert(CheckDimension(size1, size2, size3));

        if (size1 == size1_ && size2 == size2_ && size3 == size3_) return;

        std::vector<T> data(data_);
        data_.clear();
        data_.resize(size1 * size2 * size3, value);

        int min_size1 = std::min(size1, size1_);
        int min_size2 = std::min(size2, size2_);
        int min_size3 = std::min(size3, size3_);

        for (int i = 0; i < min_size1; ++i) {
            for (int j = 0; j < min_size2; ++j) {
                for (int k = 0; k < min_size3; ++k) {
                    data_[i * size2 * size3 + j * size3 + k] =
                            data[i * size2_ * size3_ + j * size3_ + k];
                }
            }
        }

        size1_ = size1;
        size2_ = size2;
        size3_ = size3;
        size23_ = size2_ * size3_;
        size_ = size1_ * size2_ * size3_;
    }

    /**
     * @return the size of first dimension of 3d array.
     */
    int size1() const {
        return size1_;
    }

    /**
     * @return the size of second dimension of 3d array.
     */
    int size2() const {
        return size2_;
    }

    /**
     * @return the size of third dimension of 3d array.
     */
    int size3() const {
        return size3_;
    }

    /**
     * @return the size of data (equal to size1 * size2 * size3).
     */
    int size() const {
        return size_;
    }

    /**
     * @return true if 3d array is empty.
     */
    bool empty() const {
        return size_ == 0;
    }

    /**
     * @return the const reference of data.
     */
    const std::vector<T>& data() const {
        return data_;
    }

    /**
     * @return the reference of data.
     */
    std::vector<T>& data() {
        return data_;
    }

    /**
     *  Fill the data of 3d array with given value.
     */
    void Fill(const T& value) {
        std::fill(data_.begin(), data_.end(), value);
    }

    /**
     * Return the value at position (i, j, k).
     * This operator allows for easy, array-style, data access.
     * Note that data access with this operator is unchecked.
     * (For checked lookups see at(int, int, int).)
     */
    ConstReference operator() (int i, int j, int k) const {
        return data_[i * size23_ + j * size3_ + k];
    }

    /**
     * Return the reference at position (row, column).
     * This operator allows for easy, array-style, data access.
     * Note that data access with this operator is unchecked.
     * (For checked lookups see at(int, int, int).)
     */
    Reference operator() (int i, int j, int k) {
        return data_[i * size23_ + j * size3_ + k];
    }

    /**
     * Return the value at position (i, j, k).
     */
    ConstReference at(int i, int j, int k) const {
        assert(0 <= i && i < size1_);
        assert(0 <= j && j < size2_);
        assert(0 <= k && k < size3_);

        return data_[i * size23_ + j * size3_ + k];
    }

    /**
     * Return the reference at position (i, j, k).
     */
    Reference at(int i, int j, int k) {
        assert(0 <= i && i < size1_);
        assert(0 <= j && j < size2_);
        assert(0 <= k && k < size3_);

        return data_[i * size23_ + j * size3_ + k];
    }

    Iterator begin()                    { return data_.begin();  }
    Iterator end()                      { return data_.end();    }
    ConstIterator begin()         const { return data_.begin();  }
    ConstIterator end()           const { return data_.end();    }
    ReverseIterator rbegin()            { return data_.rbegin(); }
    ReverseIterator rend()              { return data_.rend();   }
    ConstReverseIterator rbegin() const { return data_.rbegin(); }
    ConstReverseIterator rend()   const { return data_.rend();   }

protected:
    /**
     * Check if the given dimension is valid.
     */
    static bool CheckDimension(int dimension1, int dimension2, int dimension3) {
        if (dimension1 < 0 || dimension2 < 0 || dimension3 < 0) return false;

        // Check if multiplication is overflow.
        if (dimension2 != 0 &&
            dimension1 > std::numeric_limits<int>::max() / dimension2)
            return false;

        int tmp = dimension1 * dimension2;
        if (dimension3 != 0 &&
            tmp > std::numeric_limits<int>::max() / dimension3)
            return false;

        return true;
    }

    int size1_;           // The size of first dimension of 3d array.
    int size2_;           // The size of second dimension of 3d array.
    int size3_;           // The size of third dimension of 3d array.
    int size_;            // The size of data (equal to size1 * size2 * size3).
    int size23_;          // Equal to size2 * size3, for fast computation.
    std::vector<T> data_; // The data of 3d array.
};

} // namespace cl

#endif // UTIL_ARRAY_ARRAY_3D_H_
