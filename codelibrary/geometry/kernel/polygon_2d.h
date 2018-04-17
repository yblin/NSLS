//
// Copyright 2011 Yangbin Lin. All Rights Reserved.
//
// Author: yblin.xmu@qq.com (Yangbin Lin)
//
// This file is part of the Code Library.
//

#ifndef GEOMETRY_KERNEL_POLYGON_2D_H_
#define GEOMETRY_KERNEL_POLYGON_2D_H_

#include <algorithm>
#include <vector>

#include "codelibrary/geometry/kernel/box_2d.h"
#include "codelibrary/geometry/kernel/point_2d.h"
#include "codelibrary/geometry/kernel/segment_2d.h"
#include "codelibrary/geometry/kernel/orientation_2d.h"

namespace cl {

/// 2D Simple Polygon2D.
/**
 * A polygon is a closed chain of edges, it store as a point sequence, the
 * orientation of chain is anticlockwise.
 * The template of polygon class is used to give the value type of point.
 */
template <typename T>
class Polygon2D {
    typedef Point2D<T> Point;

public:
    typedef T value_type;

    Polygon2D()
        : size_(0) {}

    explicit Polygon2D(const std::vector<Point>& points)
        : size_(0), points_(points) {
        Initialize();
    }

    template <typename Iterator>
    Polygon2D(Iterator first, Iterator last)
        : size_(0), points_(first, last) {
        Initialize();
    }

    /**
     * Construct a rectangle polygon from box.
     */
    explicit Polygon2D(const Box2D<T>& box) {
        if (box.empty()) return;

        points_.push_back(Point(box.x_min(), box.y_min()));
        points_.push_back(Point(box.x_max(), box.y_min()));
        points_.push_back(Point(box.x_max(), box.y_max()));
        points_.push_back(Point(box.x_min(), box.y_max()));
        Initialize();
    }

    bool empty() const {
        return size_ == 0;
    }

    void clear() {
        box_ = Box2D<T>();
        points_.clear();
        size_ = 0;
    }

    /**
     * @return the size of vertices.
     */
    int size() const {
        return size_;
    }

    /**
     * @return the area of polygon.
     */
    double Area() const {
        double s = 0.0;
        for (int i = 0; i < size_; ++i) {
            s += static_cast<double>(points_[i].x) * points_[i + 1].y -
                 static_cast<double>(points_[i + 1].x) * points_[i].y;
        }
        return std::fabs(s) / 2.0;
    }

    /**
     * Get the index-th edge of polygon.
     */
    const Segment2D<T> edge(int index) const {
        assert(index >= 0 && index < size_);

        return Segment2D<T>(points_[index], points_[index + 1]);
    }

    const std::vector<Point>& points() const {
        return points_;
    }

    const Box2D<T>& box() const {
        return box_;
    }

    int left_most()     const { return left_most_;   }
    int right_most()    const { return right_most_;  }
    int top_most()      const { return top_most_;    }
    int bottom_most()   const { return bottom_most_; }

private:
    /**
     * Initialize the polygon.
     */
    void Initialize() {
        if (points_.empty()) return;

        points_.push_back(points_.front());

        // Erase the duplicate points.
        points_.resize(std::unique(points_.begin(), points_.end()) -
                       points_.begin());

        size_ = static_cast<int>(points_.size()) - 1;
        assert(size_ >= 0);

        if (size_ < 3) {
            points_.clear();
            size_ = 0;
            return;
        }

        // Get indexes of most left, right, top and bottom points and the
        // bounding box.
        GetBounding();

        // Change the orientation to anticlockwise.
        SetOrientation();
    }

    /**
     * Found the next index of point to i.
     */
    int Next(int i) const {
        assert(0 <= i && i < size_);
        return (i == size_ - 1) ? 0 : i + 1;
    }

    /**
     * Found the previous index of point to i.
     */
    int Prev(int i) const {
        assert(0 <= i && i < size_);
        return (i == 0) ? size_ - 1 : i - 1;
    }

    /**
     * Set the orientation to anticlockwise.
     */
    void SetOrientation() {
        int next = Next(left_most_);
        int prev = Prev(left_most_);

        if (!geometry::LeftTurn(points_[prev], points_[left_most_],
                                points_[next])) {
            std::reverse(points_.begin(), points_.end());
        }
    }

    /**
     * Get indexes of most left, right, top and bottom points
     * and the bounding box.
     */
    void GetBounding() {
        left_most_ = 0;
        right_most_ = 0;
        top_most_ = 0;
        bottom_most_ = 0;
        for (int i = 1; i < size_; ++i) {
            if (points_[i].x < points_[left_most_].x ||
                    (points_[i].x == points_[left_most_].x &&
                     points_[i].y < points_[left_most_].y)) {
                left_most_ = i;
            }
            if (points_[i].x > points_[right_most_].x ||
                    (points_[i].x == points_[right_most_].x &&
                     points_[i].y > points_[right_most_].y)) {
                right_most_ = i;
            }
            if (points_[i].y > points_[top_most_].y ||
                    (points_[i].y == points_[top_most_].y &&
                     points_[i].x > points_[top_most_].x)) {
                top_most_ = i;
            }
            if (points_[i].y < points_[bottom_most_].y ||
                    (points_[i].y == points_[bottom_most_].y &&
                     points_[i].x < points_[bottom_most_].x)) {
                bottom_most_ = i;
            }
        }

        box_ = Box2D<T>(points_[left_most_].x, points_[right_most_].x,
                        points_[bottom_most_].y, points_[top_most_].y);
    }

    // The point size of polygon.
    int size_;

    // The contour point set of polygon, the orientation is anticlockwise.
    std::vector<Point> points_;

    // The bounding box of polygon.
    Box2D<T> box_;

    // Index of most left point, if there are more than one points,
    // choose the more bottom one.
    int left_most_;

    // Index of most right point, if there are more than one points,
    // choose the more top one.
    int right_most_;

    // Index of most top point, if there are more than one points,
    // choose the more right one.
    int top_most_;

    // Index of most bottom point, if there are more than one points,
    // choose the more left one.
    int bottom_most_;
};

typedef Polygon2D<int>    IPolygon2D;
typedef Polygon2D<double> RPolygon2D;

} // namespace cl

#endif // GEOMETRY_KERNEL_POLYGON_2D_H_
