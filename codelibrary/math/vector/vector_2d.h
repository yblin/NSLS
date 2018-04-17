//
// Copyright 2011 Yangbin Lin. All Rights Reserved.
//
// Author: yblin.xmu@qq.com (Yangbin Lin)
//
// This file is part of the Code Library.
//

#ifndef MATH_VECTOR_VECTOR_2D_H_
#define MATH_VECTOR_VECTOR_2D_H_

#include <cassert>
#include <cmath>

namespace cl {

/// 2D Vector.
template<typename T>
class Vector2D {
public:
    typedef T value_type;

    Vector2D()
        : x(0), y(0) {}

    Vector2D(const T& x1, const T& y1)
        : x(x1), y(y1) {}

    bool operator ==(const Vector2D& rhs) const {
        return x == rhs.x && y == rhs.y;
    }

    bool operator !=(const Vector2D& rhs) const {
        return x != rhs.x || y != rhs.y;
    }

    bool operator < (const Vector2D& rhs) const {
        return x < rhs.x || (x == rhs.x && y < rhs.y);
    }

    bool operator <=(const Vector2D& rhs) const {
        return x < rhs.x || (x == rhs.x && y <= rhs.y);
    }

    bool operator > (const Vector2D& rhs) const {
        return x > rhs.x || (x == rhs.x && y > rhs.y);
    }

    bool operator >=(const Vector2D& rhs) const {
        return x > rhs.x || (x == rhs.x && y >= rhs.y);
    }

    const Vector2D& operator +=(const Vector2D& rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    const Vector2D& operator -=(const Vector2D& rhs) {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    const Vector2D& operator *=(const T& rhs) {
        x *= rhs;
        y *= rhs;
        return *this;
    }

    const Vector2D& operator /=(const T& rhs) {
        assert(rhs != 0);

        x /= rhs;
        y /= rhs;
        return *this;
    }

    /**
     * Normalize the vector.
     */
    void Normalize() {
        double len = length();
        if (len == 0.0) {
            x = 0;
            y = 0;
        } else {
            x /= len;
            y /= len;
        }
    }

    /**
     * Return the lenght of 2d vector.
     */
    double length() const {
        return std::sqrt(static_cast<double>(x) * x +
                         static_cast<double>(y) * y);
    }

    /**
     * Return the i-th component value of vector.
     */
    const T& operator[] (int i) const {
        return i == 0 ? x : y;
    }

    /**
     * Return the reference value of the i-th component of vector.
     */
    T& operator[] (int i) {
        return i == 0 ? x : y;
    }

    /**
     * Return the i-th component value of vector.
     */
    const T& at(int i) const {
        assert(0 <= i && i < 2);

        return i == 0 ? x : y;
    }

    /**
     * Return the reference value of the i-th component of vector.
     */
    T& at(int i) {
        assert(0 <= i && i < 2);

        return i == 0 ? x : y;
    }

    int size() const { return 2; }

    friend const Vector2D operator +(const Vector2D& lhs, const Vector2D& rhs) {
        return Vector2D(lhs.x + rhs.x, lhs.y + rhs.y);
    }

    friend const Vector2D operator -(const Vector2D& lhs, const Vector2D& rhs) {
        return Vector2D(lhs.x - rhs.x, lhs.y - rhs.y);
    }

    friend const Vector2D operator -(const Vector2D& rhs) {
        return Vector2D(-rhs.x, -rhs.y);
    }

    friend const Vector2D operator *(const T& lhs, const Vector2D& rhs) {
        return Vector2D(lhs * rhs.x, lhs * rhs.y);
    }

    friend const Vector2D operator *(const Vector2D& lhs, const T& rhs) {
        return Vector2D(lhs.x * rhs, lhs.y * rhs);
    }

    friend const Vector2D operator /(const Vector2D& lhs, const T& rhs) {
        assert(rhs != 0);
        return Vector2D(lhs.x / rhs, lhs.y / rhs);
    }

    /**
     * @return the cross product of two vectors.
     *
     * Here we define the function outside this class to make sure this function
     * under the CL namespace. Otherwise, this function will under the global
     * namespace.
     */
    template <typename T1>
    friend double CrossProduct(const Vector2D<T1>& v1, const Vector2D<T1>& v2);

    /**
     * @return the dot product of two vectors.
     *
     * Here we define the function outside this class to make sure this function
     * under the CL namespace. Otherwise, this function will under the global
     * namespace.
     */
    template <typename T1>
    friend double DotProduct(const Vector2D<T1>& v1, const Vector2D<T1>& v2);

    T x; /// X component.
    T y; /// Y component.
};

typedef Vector2D<int> IVector2D;
typedef Vector2D<double> RVector2D;

/**
 * @return cross product of two vectors.
 */
template <typename T>
double CrossProduct(const Vector2D<T>& v1, const Vector2D<T>& v2) {
    return static_cast<double>(v1.x) * v2.y - static_cast<double>(v2.x) * v1.y;
}

/**
 * @return dot product of two vectors.
 */
template <typename T>
double DotProduct(const Vector2D<T>& v1, const Vector2D<T>& v2) {
    return static_cast<double>(v1.x) * v2.x + static_cast<double>(v1.y) * v2.y;
}

} // namespace cl

#endif // MATH_VECTOR_VECTOR_2D_H_
