//
// Copyright 2012 Yangbin Lin. All Rights Reserved.
//
// Author: yblin.xmu@qq.com (Yangbin Lin)
//
// This file is part of the Code Library.
//

#ifndef GEOMETRY_KERNEL_MULTI_POLYGON_2D_H_
#define GEOMETRY_KERNEL_MULTI_POLYGON_2D_H_

#include <vector>

#include "codelibrary/geometry/kernel/polygon_2d.h"

namespace cl {

/// The Multi Boundary Polygon.
/**
 * A multi-polygon is a set of polygon with boundary flag (inner or outer).
 *
 * It must uphold the following conditions:
 *   1. Every boundaries must be a simple polygon.
 *   2. All boundaries must be disjoint from others (except on vertices).
 */
template <typename T>
class MultiPolygon2D {
    typedef Polygon2D<T> Polygon;

public:
    typedef T value_type;

    /// The boundary for multi-polygon
    struct Boundary {
        Boundary() {}

        Boundary(const Polygon& in_polygon, bool in_is_outer)
            : polygon(in_polygon), is_outer(in_is_outer) {}

        Polygon polygon;
        bool is_outer; // True if the this boundary is outer boundary.
    };

    MultiPolygon2D() {}

    /**
     * Construct multi-polygon with given polygon as its outer boundary.
     */
    explicit MultiPolygon2D(const Polygon& polygon) {
        if (!polygon.empty()) boundaries_.emplace_back(polygon, true);
        box_ = polygon.box();
    }

    /**
     * Return the area of the polygon.
     */
    double Area() const {
        double area = 0.0;
        for (const Boundary& b : boundaries_) {
            if (b.is_outer) {
                area += b.polygon.Area();
            } else {
                area -= b.polygon.Area();
            }
        }

        return area;
    }

    /**
     * Insert a new boundary.
     */
    void Insert(const Polygon& polygon, bool is_outer) {
        if (polygon.empty()) return;

        boundaries_.emplace_back(polygon, is_outer);
        box_.Union(polygon.box());
    }

    bool empty() const {
        return boundaries_.empty();
    }

    void clear() {
        box_ = Box2D<T>();
        boundaries_.clear();
    }

    const std::vector<Boundary>& boundaries() const {
        return boundaries_;
    }

    /**
     * Return the size of boundaries.
     */
    int size_boundaries() const {
        return boundaries_.size();
    }

    const Box2D<T>& box() const {
        return box_;
    }

private:
    Box2D<T> box_;                     // The bounding box of multi-polygon.
    std::vector<Boundary> boundaries_; // The boundaries of multi-polygon.
};

typedef MultiPolygon2D<int>    IMultiPolygon2D;
typedef MultiPolygon2D<double> RMultiPolygon2D;

} // namespace cl

#endif // GEOMETRY_KERNEL_MULTI_POLYGON_2D_H_
