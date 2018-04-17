//
// Copyright 2011 Yangbin Lin. All Rights Reserved.
//
// Author: yblin.xmu@qq.com (Yangbin Lin)
//
// This file is part of the Code Library.
//

#ifndef GEOMETRY_KERNEL_LINE_2D_H_
#define GEOMETRY_KERNEL_LINE_2D_H_

#include <cassert>

#include "codelibrary/geometry/kernel/orientation_2d.h"
#include "codelibrary/geometry/kernel/segment_2d.h"

namespace cl {

/// 2D Line.
/**
 * A 2D line can be uniquely defined by a point on line and a direction vector.
 */
template <typename T>
class Line2D {
public:
    typedef T value_type;

    Line2D() {}

    /**
     * Construct from a point on the line and direction of line.
     */
    Line2D(const Point2D<T>& p, const Vector2D<T>& direction)
        : point_(p), direction_(direction) {}

    /**
     * Construct from two distinct points.
     */
    Line2D(const Point2D<T>& p1, const Point2D<T>& p2) {
        assert(p1 != p2);

        point_ = p1;
        direction_ = p2 - p1;
    }

    /**
     * Construct from segment.
     */
    explicit Line2D(const Segment2D<T>& segment) {
        assert(segment.lower_point() != segment.upper_point());

        point_ = segment.lower_point();
        direction_ = segment.direction();
    }

    bool empty() const {
        return direction_.x == 0 && direction_.y == 0;
    }

    const Vector2D<T> direction() const {
        return direction_;
    }

    const Point2D<T>& point() const {
        return point_;
    }

private:
    Point2D<T> point_;      // A point on the line.
    Vector2D<T> direction_; // The direction vector of line.
};

typedef Line2D<int>    ILine2D;
typedef Line2D<double> RLine2D;

} // namespace cl

#endif // GEOMETRY_KERNEL_LINE_2D_H_
