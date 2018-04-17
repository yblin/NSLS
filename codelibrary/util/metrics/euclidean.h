//
// Copyright 2014 Yangbin Lin. All Rights Reserved.
//
// Author: yblin.xmu@qq.com (Yangbin Lin)
//
// This file is part of the Code Library.
//

#ifndef UTIL_METRICS_EUCLIDEAN_H_
#define UTIL_METRICS_EUCLIDEAN_H_

#include <cassert>
#include <cmath>

#include "codelibrary/base/macros.h"

namespace cl {
namespace metrics {

/**
 * Euclidean distance for two n-dimensional points.
 */
class Euclidean {
public:
    Euclidean() {}

    template <typename T>
    double operator() (const T& a, const T& b) const {
        assert(a.size() == b.size());

        double t = 0.0;
        for (int i = 0; i < a.size(); ++i) {
            t += static_cast<double>(a[i] - b[i]) * (a[i] - b[i]);
        }

        return std::sqrt(t);
    }

private:
    DISALLOW_COPY_AND_ASSIGN(Euclidean);
};

} // namespace metrics
} // namespace cl

#endif // UTIL_METRICS_EUCLIDEAN_H_
