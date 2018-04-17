//
// Copyright 2011 Yangbin Lin. All Rights Reserved.
//
// Author: yblin.xmu@qq.com (Yangbin Lin)
//
// This file is part of the Code Library.
//

#ifndef GEOMETRY_KERNEL_SEGMENT_2D_H_
#define GEOMETRY_KERNEL_SEGMENT_2D_H_

#include <algorithm>

#include "codelibrary/geometry/kernel/point_2d.h"
#include "codelibrary/geometry/kernel/box_2d.h"

namespace cl {

/// 2D Line Segment.
template <typename T>
class Segment2D {
    typedef Point2D<T> Point;

public:
    typedef T value_type;

    Segment2D() {}

    Segment2D(const Point& p1, const Point& p2)
        : lower_point_(std::min(p1, p2)),
          upper_point_(std::max(p1, p2)),
          box_(std::min(p1.x, p2.x), std::max(p1.x, p2.x),
               std::min(p1.y, p2.y), std::max(p1.y, p2.y)) {}

    /**
     * The left bottom endpoint of line segment.
     */
    const Point& lower_point() const {
        return lower_point_;
    }

    /**
     * The right top endpoint of line segment.
     */
    const Point& upper_point() const {
        return upper_point_;
    }

    /**
     * The bounding box of line segment.
     */
    const Box2D<T>& box() const {
        return box_;
    }

    /**
     * Return the direction of line segment.
     */
    const Vector2D<T> direction() const {
        return upper_point_ - lower_point_;
    }

    /**
     * Return the length of line segment.
     */
    double length() const {
        return direction().length();
    }

    bool operator ==(const Segment2D& rhs) const {
        return lower_point_ == rhs.lower_point_ &&
               upper_point_ == rhs.upper_point_;
    }

    bool operator !=(const Segment2D& rhs) const {
        return !(*this == rhs);
    }

    bool operator <(const Segment2D& rhs) const {
        return lower_point_ < rhs.lower_point_ ||
               (lower_point_ == rhs.lower_point_ &&
                upper_point_ < rhs.upper_point_);
    }

private:
    Point lower_point_; // The left bottom endpoint of line segment.
    Point upper_point_; // The right top endpoint of line segment.
    Box2D<T> box_;      // The bounding box of line segment.
};

typedef Segment2D<int>    ISegment2D;
typedef Segment2D<double> RSegment2D;

} // namespace cl

#endif // GEOMETRY_KERNEL_SEGMENT_2D_H_
