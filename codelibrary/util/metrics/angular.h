//
// Copyright 2014 Yangbin Lin. All Rights Reserved.
//
// Author: yblin.xmu@qq.com (Yangbin Lin)
//
// This file is part of the Code Library.
//

#ifndef UTIL_METRICS_ANGULAR_H_
#define UTIL_METRICS_ANGULAR_H_

#include "codelibrary/base/constants.h"
#include "codelibrary/base/macros.h"
#include "codelibrary/util/metrics/cosine.h"

namespace cl {
namespace metrics {

/**
 * The metrics to measure the angle between two vectors.
 *
 * The range of angular metrics is [0, 1].
 */
class Angular {
public:
    Angular() {}

    template <typename T>
    double operator() (const T& a, const T& b) const {
        return std::acos(cosine_(a, b)) / PI;
    }

private:
    Cosine cosine_;

    DISALLOW_COPY_AND_ASSIGN(Angular);
};

} // namespace metrics
} // namespace cl

#endif // UTIL_METRICS_ANGULAR_H_
