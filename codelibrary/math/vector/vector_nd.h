//
// Copyright 2013 Yangbin Lin. All Rights Reserved.
//
// Author: yblin.xmu@qq.com (Yangbin Lin)
//
// This file is part of the Code Library.
//

#ifndef MATH_VECTOR_VECTOR_ND_H_
#define MATH_VECTOR_VECTOR_ND_H_

#include <algorithm>
#include <cassert>
#include <cmath>
#include <functional>
#include <vector>

#include "codelibrary/math/vector/vector_2d.h"
#include "codelibrary/math/vector/vector_3d.h"

namespace cl {

/// N-dimensional Vector.
template<typename T>
class VectorND {
public:
    typedef T value_type;

    VectorND()
        : size_(0) {}

    explicit VectorND(const Vector2D<T>& v)
        : size_(2),
          data_(2) {
        data_[0] = v.x;
        data_[1] = v.y;
    }

    explicit VectorND(const Vector3D<T>& v)
        : size_(3),
          data_(3) {
        data_[0] = v.x;
        data_[1] = v.y;
        data_[2] = v.z;
    }

    VectorND(int size, const T& value = T())
        : size_(size),
          data_(size, value) {}

    template <typename InputIter>
    VectorND(int size, InputIter first, InputIter last)
        : size_(size),
          data_(first, last) {}

    explicit VectorND(const std::vector<T>& data)
        : size_(static_cast<int>(data.size())),
          data_(data) {
        assert(size_ >= 0);
    }

    VectorND& operator = (const VectorND& v) {
        size_ = v.size_;
        data_ = v.data_;

        return *this;
    }

    VectorND& operator = (const Vector2D<T>& v) {
        size_ = 2;
        data_.resize(2);
        data_[0] = v.x;
        data_[1] = v.y;

        return *this;
    }

    VectorND& operator = (const Vector3D<T>& v) {
        size_ = 3;
        data_.resize(2);
        data_[0] = v.x;
        data_[1] = v.y;
        data_[2] = v.z;

        return *this;
    }

    /**
     * Clear the data of vector and set size to zero.
     */
    void clear() {
        data_.clear();
        size_ = 0;
    }

    /**
     * Resize the vector.
     */
    void resize(int size, const T& value = 0) {
        assert(size >= 0);

        size_ = size;
        data_.resize(size, value);
    }

    int size() const { return size_; }

    /**
     * Return true if this vector is empty.
     */
    bool empty() const {
        return size_ == 0;
    }

    /**
     *  Fill the data of vector with given value.
     */
    void Fill(const T& value) {
        std::fill(data_.begin(), data_.end(), value);
    }

    /**
     * Return the i-th component value of vector.
     */
    const T& operator[] (int i) const {
        return data_[i];
    }

    /**
     * Return the reference value of the i-th component of vector.
     */
    T& operator[] (int i) {
        return data_[i];
    }

    /**
     * Return the i-th component value of vector.
     */
    const T& at(int i) const {
        assert(0 <= i && i < size_);

        return data_[i];
    }

    /**
     * Return the reference value of the i-th component of vector.
     */
    T& at(int i) {
        assert(0 <= i && i < size_);

        return data_[i];
    }

    bool operator ==(const VectorND& rhs) const {
        assert(size_ == rhs.size_);

        return std::equal(data_.begin(), data_.end(), rhs.data_.begin());
    }

    bool operator !=(const VectorND& rhs) const {
        return !(*this == rhs);
    }

    bool operator < (const VectorND& rhs) const {
        assert(size_ == rhs.size_);

        return std::lexicographical_compare(data_.begin(), data_.end(),
                                            rhs.data_.begin(), rhs.data_.end());
    }

    bool operator <=(const VectorND& rhs) const {
        assert(size_ == rhs.size_);

        return std::lexicographical_compare(data_.begin(), data_.end(),
                                            rhs.data_.begin(), rhs.data_.end(),
                                            std::less_equal<T>());
    }

    bool operator > (const VectorND& rhs) const {
        return !(*this <= rhs);
    }

    bool operator >=(const VectorND& rhs) const {
        return !(*this < rhs);
    }

    const VectorND& operator +=(const VectorND& rhs) {
        assert(size_ == rhs.size_);

        for (int i = 0; i < size_; ++i) {
            data_[i] += rhs.data_[i];
        }
        return *this;
    }

    const VectorND& operator -=(const VectorND& rhs) {
        assert(size_ == rhs.size_);

        for (int i = 0; i < size_; ++i) {
            data_[i] -= rhs.data_[i];
        }
        return *this;
    }

    const VectorND& operator *=(const T& rhs) {
        for (int i = 0; i < size_; ++i) {
            data_[i] *= rhs;
        }
        return *this;
    }

    const VectorND& operator /=(const T& rhs) {
        assert(rhs != 0);

        for (int i = 0; i < size_; ++i) {
            data_[i] /= rhs;
        }
        return *this;
    }

    /**
     * Normalize the vector.
     */
    void Normalize() {
        double len = length();
        if (len == 0.0) {
            std::fill(data_.begin(), data_.end(), T(0));
        } else {
            for (int i = 0; i < size_; ++i) {
                data_[i] /= len;
            }
        }
    }

    /**
     * Return the length (Euclidean norm) of vector.
     */
    double length() const {
        double norm = 0.0;
        for (int i = 0; i < size_; ++i) {
            norm += static_cast<double>(data_[i]) * data_[i];
        }
        return std::sqrt(norm);
    }

    /**
     * Convert vector to vector2D, require 'size_ == 2'.
     */
    const Vector2D<T> ToVector2D() const {
        assert(size_ == 2);

        return Vector2D<T>(data_[0], data_[1]);
    }

    /**
     * Convert vector to vector3D, Require 'size_ == 3'.
     */
    const Vector3D<T> ToVector3D() const {
        assert(size_ == 3);

        return Vector3D<T>(data_[0], data_[1], data_[2]);
    }

    const std::vector<T>& data() const {
        return data_;
    }

    friend const VectorND operator +(const VectorND& lhs, const VectorND& rhs) {
        assert(lhs.size_ == rhs.size_);

        VectorND v(lhs.size());
        for (int i = 0; i < v.size_; ++i) {
            v.data_[i] = lhs.data_[i] + rhs.data_[i];
        }
        return v;
    }

    friend const VectorND operator -(const VectorND& lhs, const VectorND& rhs) {
        assert(lhs.size_ == rhs.size_);

        VectorND v(lhs.size());
        for (int i = 0; i < v.size_; ++i) {
            v.data_[i] = lhs.data_[i] - rhs.data_[i];
        }
        return v;
    }

    friend const VectorND operator -(const VectorND& rhs) {
        VectorND v(rhs.size());
        for (int i = 0; i < v.size_; ++i) {
            v.data_[i] = -rhs.data_[i];
        }
        return v;
    }

    friend const VectorND operator *(const T& lhs, const VectorND& rhs) {
        VectorND v(rhs.size());
        for (int i = 0; i < v.size_; ++i) {
            v.data_[i] = lhs * rhs.data_[i];
        }
        return v;
    }

    friend const VectorND operator *(const VectorND& lhs, const T& rhs) {
        VectorND v(lhs.size());
        for (int i = 0; i < v.size_; ++i) {
            v.data_[i] = rhs * lhs.data_[i];
        }
        return v;
    }

    friend const VectorND operator /(const VectorND& lhs, const T& rhs) {
        assert(rhs != 0);

        VectorND v(lhs.size_);
        for (int i = 0; i < v.size_; ++i) {
            v.data_[i] = lhs.data_[i] / rhs;
        }
        return v;
    }

    /**
     * @return the dot product of two vectors.
     *
     * Here we define the function outside this class to make sure this function
     * under the CL namespace. Otherwise, this function will under the global
     * namespace.
     */
    template <typename T1>
    friend double DotProduct(const VectorND<T1>& v1, const VectorND<T1>& v2);

private:
    int size_;            // The size of vector.
    std::vector<T> data_; // The data of vector.
};

typedef VectorND<int> IVectorND;
typedef VectorND<double> RVectorND;

/**
 * @return the dot product of two vectors.
 */
template <typename T>
double DotProduct(const VectorND<T>& v1, const VectorND<T>& v2) {
    assert(v1.size_ == v2.size_);

    double sum = 0.0;
    for (int i = 0; i < v1.size_; ++i) {
        sum += static_cast<double>(v1.data_[i]) * v2.data_[i];
    }
    return sum;
}

} // namespace cl

#endif // MATH_VECTOR_VECTOR_ND_H_
