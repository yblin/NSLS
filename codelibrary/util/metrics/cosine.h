//
// Copyright 2014 Yangbin Lin. All Rights Reserved.
//
// Author: yblin.xmu@qq.com (Yangbin Lin)
//
// This file is part of the Code Library.
//

#ifndef UTIL_METRICS_COSINE_H_
#define UTIL_METRICS_COSINE_H_

#include <cmath>

#include "codelibrary/base/macros.h"

namespace cl {
namespace metrics {

/**
 * Cosine is a measure of similarity between two vectors of an inner product
 * space that measures the cosine of the angle between them.
 *
 * The range of cosine metrics is [-1, 1].
 */
class Cosine {
public:
    Cosine() {}

    template <typename T>
    double operator() (const T& a, const T& b) const {
        assert(a.size() == b.size());

        double t0 = 0.0, t1 = 0.0, t2 = 0.0;
        for (int i = 0; i < a.size(); ++i) {
            t0 += static_cast<double>(a[i]) * b[i];
            t1 += static_cast<double>(a[i]) * a[i];
            t2 += static_cast<double>(b[i]) * b[i];
        }

        return t0 / std::sqrt(t1 * t2);
    }

private:
    DISALLOW_COPY_AND_ASSIGN(Cosine);
};

} // namespace metrics
} // namespace cl

#endif // UTIL_METRICS_COSINE_H_
