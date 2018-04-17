//
// Copyright 2014 Yangbin Lin. All Rights Reserved.
//
// Author: yblin.xmu@qq.com (Yangbin Lin)
//
// This file is part of the Code Library.
//

#ifndef UTIL_METRICS_MANHATTAN_H_
#define UTIL_METRICS_MANHATTAN_H_

#include <cassert>
#include <cmath>

#include "codelibrary/base/macros.h"

namespace cl {
namespace metrics {

/**
 * Manhattan distance for two n-dimensional points.
 */
class Manhattan {
public:
    Manhattan() {}

    template <typename T>
    double operator() (const T& a, const T& b) const {
        assert(a.size() == b.size());

        double t = 0.0;
        for (int i = 0; i < a.size(); ++i) {
            t += std::fabs(a[i] - b[i]);
        }

        return t;
    }

private:
    DISALLOW_COPY_AND_ASSIGN(SquaredEuclidean);
};

} // namespace metrics
} // namespace cl

#endif // UTIL_METRICS_MANHATTAN_H_
