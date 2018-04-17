//
// Copyright 2011 Yangbin Lin. All Rights Reserved.
//
// Author: yblin.xmu@qq.com (Yangbin Lin)
//
// This file is part of the Code Library.
//

#ifndef GEOMETRY_KERNEL_BOX_2D_H_
#define GEOMETRY_KERNEL_BOX_2D_H_

#include <algorithm>
#include <cassert>

#include "codelibrary/math/vector.h"

namespace cl {

/// 2D Axis-Aligned Minimum Bounding Box.
/**
 * The axis-aligned minimum bounding box for a given point set is its minimum
 * bounding box subject to the constraint that the edges of the box are parallel
 * to the (Cartesian) coordinate axis.
 */
template <typename T>
class Box2D {
public:
    typedef T value_type;

    /**
     * The defualt box is an empty box, so that the lower bounds are greater
     * than upper bounds here.
     */
    Box2D() : x_min_(1), x_max_(0), y_min_(1), y_max_(0) {}

    /**
     * Require lower bounds no greater than upper bounds.
     */
    Box2D(const T& x_min, const T& x_max, const T& y_min, const T& y_max)
        : x_min_(x_min), x_max_(x_max), y_min_(y_min), y_max_(y_max) {
        assert(x_min_ <= x_max_ && y_min_ <= y_max_);
    }

    template <typename Iterator>
    Box2D(Iterator first, Iterator last)
        : Box2D() {
        if (first == last) return;

        Iterator i = first;
        x_min_ = x_max_ = (*i)[0];
        y_min_ = y_max_ = (*i)[1];

        for (++i; i != last; ++i) {
            x_min_ = std::min(x_min_, (*i)[0]);
            x_max_ = std::max(x_max_, (*i)[0]);
            y_min_ = std::min(y_min_, (*i)[1]);
            y_max_ = std::max(y_max_, (*i)[1]);
        }
    }

    /**
     * The lower x value of box.
     */
    const T& x_min() const {
        return x_min_;
    }

    /**
     * The higher x value of box.
     */
    const T& x_max() const {
        return x_max_;
    }

    /**
     * The lower y value of box.
     */
    const T& y_min() const {
        return y_min_;
    }

    /**
     * The higher y value of box.
     */
    const T& y_max() const {
        return y_max_;
    }

    /**
     * Check if the box is empty.
     */
    bool empty() const {
        return x_min_ > x_max_ || y_min_ > y_max_;
    }

    bool operator ==(const Box2D& rhs) const {
        return x_min_ == rhs.x_min_ && x_max_ == rhs.x_max_ &&
               y_min_ == rhs.y_min_ && y_max_ == rhs.y_max_;
    }

    bool operator !=(const Box2D& rhs) const {
        return x_min_ != rhs.x_min_ || x_max_ != rhs.x_max_ ||
               y_min_ != rhs.y_min_ || y_max_ != rhs.y_max_;
    }

    /**
     * @return the X length of box.
     * @note that x_length may be negative if x_max_ and x_min_ are extreme.
     */
    const T x_length() const {
        return empty() ? 0 : x_max_ - x_min_;
    }

    /**
     * @return the Y length of box.
     * @note that y_length may be negative if y_max_ and y_min_ are extreme.
     */
    const T y_length() const {
        return empty() ? 0 : y_max_ - y_min_;
    }

    /**
     * @return the bounding box of this box (itself).
     */
    const Box2D<T>& box() const {
        return *this;
    }

    /**
     * Union this box with anthor box, the result is the hull of two boxes.
     */
    void Union(const Box2D& box) {
        if (empty()) {
            *this = box;
            return;
        }
        if (box.empty()) return;

        x_min_ = std::min(x_min_, box.x_min_);
        y_min_ = std::min(y_min_, box.y_min_);
        x_max_ = std::max(x_max_, box.x_max_);
        y_max_ = std::max(y_max_, box.y_max_);
    }

    /**
     * Intersect this box with anthor box.
     */
    void Intersection(const Box2D& box) {
        if (empty() || box.empty()) {
            *this = Box2D<T>();
            return;
        }

        x_min_ = std::max(x_min_, box.x_min_);
        y_min_ = std::max(y_min_, box.y_min_);
        x_max_ = std::min(x_max_, box.x_max_);
        y_max_ = std::min(y_max_, box.y_max_);

        if (x_min_ > x_max_ || y_min_ > y_max_) *this = Box2D<T>();
    }

    /**
     * @return true if this box is intersected with the other box.
     */
    bool IsIntersect(const Box2D& box) const {
        if (empty() || box.empty()) return false;

        return x_max_ >= box.x_min_ && x_min_ <= box.x_max_ &&
               y_max_ >= box.y_min_ && y_min_ <= box.y_max_;
    }

    /**
     * @return true if this box is overlap with the other box
     *         (intersected but not touch).
     */
    bool IsOverlap(const Box2D& box) const {
        if (empty() || box.empty()) return false;

        return x_max_ > box.x_min_ && x_min_ < box.x_max_ &&
               y_max_ > box.y_min_ && y_min_ < box.y_max_;
    }

private:
    T x_min_; // The lower x value of box.
    T x_max_; // The higher x value of box.
    T y_min_; // The lower y value of box.
    T y_max_; // The higher y value of box.
};

typedef Box2D<int>    IBox2D;
typedef Box2D<double> RBox2D;

} // namespace cl

#endif // GEOMETRY_KERNEL_BOX_2D_H_
