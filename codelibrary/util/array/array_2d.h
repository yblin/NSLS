//
// Copyright 2011 Yangbin Lin. All Rights Reserved.
//
// Author: yblin.xmu@qq.com (Yangbin Lin)
//
// This file is part of the Code Library.
//

#ifndef UTIL_ARRAY_ARRAY_2D_H_
#define UTIL_ARRAY_ARRAY_2D_H_

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <limits>
#include <vector>

namespace cl {

/// 2D Array.
/**
 * This class is as most efficient as C-style 2d array.
 * User can access the data of Array2D by () operator.
 */
template<typename T>
class Array2D {
    typedef typename std::vector<T>::reference       Reference;
    typedef typename std::vector<T>::const_reference ConstReference;

public:
    typedef typename std::vector<T>::iterator Iterator;
    typedef typename std::vector<T>::const_iterator ConstIterator;
    typedef typename std::vector<T>::reverse_iterator ReverseIterator;
    typedef typename std::vector<T>::const_reverse_iterator
                     ConstReverseIterator;

    Array2D()
        : rows_(0), columns_(0), size_(0) {}

    Array2D(int rows, int columns, const T& value = T())
        : rows_(rows), columns_(columns),
          size_(rows * columns) {
        assert(CheckDimension(rows, columns));

        data_.resize(size_, value);
    }

    template <typename InputIterator>
    Array2D(int rows, int columns, InputIterator first, InputIterator last)
        : rows_(rows), columns_(columns),
          size_(rows * columns),
          data_(first, last) {
        assert(size_ == static_cast<int>(data_.size()));
    }

    /**
     * Clear the data of 2d array and set rows and columns to zero.
     */
    void clear() {
        std::vector<T>().swap(data_);  // Clear the data by swap trick.
        rows_ = 0;
        columns_ = 0;
        size_ = 0;
    }

    /**
     * Resize the 2d array.
     *
     * @param rows    - the rows after resize.
     * @param columns - the columns after resize.
     * @param value   - the default value to fill the extra 2d array data.
     */
    void Resize(int rows, int columns, const T& value = T()) {
        assert(CheckDimension(rows, columns));

        if (columns == columns_) {
            rows_ = rows;
            size_ = rows * columns;
            data_.resize(size_, value);
        } else {
            size_ = rows * columns;
            std::vector<T> data = data_;
            data_.resize(size_);
            std::fill(data_.begin(), data_.end(), value);

            int min_rows = std::min(rows_, rows);
            int min_columns = std::min(columns_, columns);
            for (int i = 0; i < min_rows; ++i) {
                std::copy_n(data.begin() + i * columns_, min_columns,
                            data_.begin() + i * columns);
            }
            rows_ = rows;
            columns_ = columns;
        }
    }

    /**
     * Return the rows of 2d array.
     */
    int rows() const {
        return rows_;
    }

    /**
     * Return the columns of 2d array.
     */
    int columns() const {
        return columns_;
    }

    /**
     * Return the size (rows * columns) of 2d array.
     */
    int size() const {
        return size_;
    }

    /**
     * Return the reference of raw data.
     */
    std::vector<T>& data() {
        return data_;
    }

    /**
     * Return the const reference of raw data.
     */
    const std::vector<T>& data() const {
        return data_;
    }

    /**
     * Return true if 2d array is empty.
     */
    bool empty() const {
        return size_ == 0;
    }

    /**
     * Get the sub-array.
     *
     * @param r1, c1 - the left top coordinate of sub-array is (r1, c1).
     * @param r2, c2 - the right bottom coordinate of sub-array is (r2, c2).
     */
    const Array2D SubArray(int r1, int c1, int r2, int c2) const {
        assert(0 <= r1 && r1 < rows_);
        assert(0 <= r2 && r2 < rows_);
        assert(0 <= c1 && c1 < columns_);
        assert(0 <= c2 && c2 < columns_);
        assert(r1 <= r2 && c1 <= c2);

        Array2D sub_array(r2 - r1 + 1, c2 - c1 + 1);
        int k = 0;
        for (int i = r1; i <= r2; ++i) {
            int offset = i * columns_;
            for (int j = c1; j <= c2; ++j) {
                sub_array.data_[k++] = data_[offset + j];
            }
        }
        return sub_array;
    }

    /**
     * Fill the data of 2d array with given value.
     */
    void Fill(const T& value) {
        std::fill(data_.begin(), data_.end(), value);
    }

    /**
     * Swap 2D array.
     */
    void Swap(Array2D* data) {
        assert(data);

        std::swap(rows_, data->rows_);
        std::swap(columns_, data->columns_);
        std::swap(size_, data->size_);
        data_.swap(*data_);
    }

    /**
     * Swap two rows.
     */
    void SwapRows(int row1, int row2) {
        assert(0 <= row1 && row1 < rows_);
        assert(0 <= row2 && row2 < rows_);

        if (row1 == row2) return;

        int offset1 = rows_ * row1;
        int offset2 = rows_ * row2;
        for (int i = 0; i < columns_; ++i) {
            std::swap(data_[offset1 + i], data_[offset2 + i]);
        }
    }

    /**
     * Swap two columns.
     */
    void SwapColumns(int column1, int column2) {
        assert(0 <= column1 && column1 < columns_);
        assert(0 <= column2 && column2 < columns_);

        if (column1 == column2) return;

        for (int i = 0; i < rows_; ++i) {
            std::swap(data_[column1], data_[column2]);
            column1 += columns_;
            column2 += columns_;
        }
    }

    /**
     * Return a row.
     */
    const std::vector<T> Row(int row) const {
        assert(0 <= row && row < rows_);

        std::vector<T> array(columns_);
        int offset = columns_ * row;
        for (int i = 0; i < columns_; ++i) {
            array[i] = data_[offset + i];
        }
        return array;
    }

    /**
     * Return a column.
     */
    const std::vector<T> Column(int column) const {
        assert(0 <= column && column < columns_);

        std::vector<T> array(rows_);
        for (int i = 0, k = column; i < rows_; ++i, k += columns_) {
            array[i] = data_[k];
        }
        return array;
    }

    /**
     * This operator allows for easy, array-style, data access.
     *
     * @return the value at position (row, column).
     * @note that, data access with this operator is unchecked. For checked
     *       lookups see at(int, int).
     */
    ConstReference operator() (int row, int column) const {
        return data_[row * columns_ + column];
    }

    /**
     * This operator allows for easy, array-style, data access.
     *
     * @return the reference at position (row, column).
     * @note that, data access with this operator is unchecked. For checked
     *       lookups see at(int, int).
     */
    Reference operator() (int row, int column) {
        return data_[row * columns_ + column];
    }

    /**
     * @return the value at position (row, column).
     */
    ConstReference at(int row, int column) const {
        assert(0 <= row && row < rows_);
        assert(0 <= column && column < columns_);

        return data_[row * columns_ + column];
    }

    /**
     * @return the reference at position (row, column).
     */
    Reference at(int row, int column) {
        assert(0 <= row && row < rows_);
        assert(0 <= column && column < columns_);

        return data_[row * columns_ + column];
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
    static bool CheckDimension(int dimension1, int dimension2) {
        if (dimension1 < 0 || dimension2 < 0) return false;

        // Check if multiplication is overflow.
        if (dimension2 != 0 &&
            dimension1 > std::numeric_limits<int>::max() / dimension2)
            return false;

        return true;
    }

    int rows_;            // The number of rows of 2d array.
    int columns_;         // The number of columns of 2d array.
    int size_;            // The size of data (equal to rows * columns).
    std::vector<T> data_; // The data of 2d array.
};

} // namespace cl

#endif // UTIL_ARRAY_ARRAY_2D_H_
