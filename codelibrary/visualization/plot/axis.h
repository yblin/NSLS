//
// Copyright 2015 Yangbin Lin. All Rights Reserved.
//
// Author: yblin.xmu@qq.com (Yangbin Lin)
//
// This file is part of the Code Library.
//

#ifndef VISUALIZATION_PLOT_AXIS_H_
#define VISUALIZATION_PLOT_AXIS_H_

#include <cassert>
#include <cfloat>
#include <cmath>
#include <string>
#include <vector>

#include "codelibrary/base/macros.h"
#include "codelibrary/base/string_printf.h"
#include "codelibrary/visualization/terminal/terminal.h"

namespace cl {
namespace plot {

/// Axis for Plot.
class Axis {
public:
    /**
     * Construct a axis by given range and maximal number of ticks.
     * @note that, the data range not necessarily the same as the axis range.
     *
     * @param min       - the expected minimum value of axis.
     * @param max       - the expected maximal value of axis.
     * @param max_ticks - the expected maximal number of ticks on the axis.
     */
    Axis(double min = 0.0, double max = 1.0, int max_ticks = 10)
        : is_increasing_(true) {
        Reset(min, max, max_ticks);
    }

    /**
     * Reset this axis.
     */
    void Reset(double min, double max, int max_ticks = 10) {
        assert(min <= max);
        assert(max_ticks > 0);

        ChooseInterval(min, max, max_ticks);
        GenerateTicks(min, max);
    }

    /**
     * @return the minimum value of axis.
     * @note that it dose not equal to the input min value.
     */
    double min() const {
        return ticks_.front();
    }

    /**
     * @return the maximal value of axis.
     * @note that it dose not equal to the input max value.
     */
    double max() const {
        return ticks_.back();
    }

    /**
     * @return the length of axis.
     */
    double length() const {
        return max() - min();
    }

    /**
     * @return the tick values.
     */
    const std::vector<double>& ticks() const {
        return ticks_;
    }

    /**
     * @return the tick labels.
     */
    const std::vector<std::string>& tick_labels() const {
        return tick_labels_;
    }

    /**
     * Reverse the direction of axis.
     */
    void Reverse() {
        is_increasing_ ^= is_increasing_;
    }

    /**
     * @return true if the axis value is increasing.
     */
    bool is_increasing() const {
        return is_increasing_;
    }

private:
    /**
     * Automatically choose a usable ticking interval.
     */
    void ChooseInterval(double min, double max, int max_ticks) {
        // Order of magitude of argument.
        double length = max - min;
        if (length == 0.0) length = 1.0;
        double power = std::pow(10.0, std::floor(std::log10(length)));

        // Approximate number of decades, we expet 1 <= xnorm <= 10.
        double xnorm = length / power;
        assert(xnorm >= 1.0);

        // Approximate number of ticks per decade.
        double n_ticks = max_ticks / xnorm;

        if (n_ticks > 20) {
            interval_ = 0.05;       // e.g. 0, 0.05, 0.10, ...
        } else if (n_ticks > 10) {
            interval_ = 0.1;        // e.g. 0, 0.1, 0.2, ...
        } else if (n_ticks > 5) {
            interval_ = 0.2;        // e.g. 0, 0.2, 0.4, ...
        } else if (n_ticks > 2) {
            interval_ = 0.5;        // e.g. 0, 0.5, 1, ...
        } else if (n_ticks > 1) {
            interval_ = 1;          // e.g. 0, 1, 2, ...
        } else if (n_ticks > 0.5) {
            interval_ = 2;          // e.g. 0, 2, 4, ...
        } else {
            interval_ = std::ceil(xnorm);
        }

        interval_ *= power;
    }

    /**
     * Generate tick values and labels.
     */
    void GenerateTicks(double min, double max) {
        double start = std::floor(min / interval_);
        double end   = std::ceil(max / interval_);

        ticks_.clear();
        for (double i = start; i <= end; ++i) {
            double x = i * interval_;
            ticks_.push_back(x);
        }
        if (ticks_.size() == 1) {
            ticks_.push_back((end + 1) * interval_);
        }

        // Generate tick labels.
        tick_labels_.clear();
        for (double x : ticks_) {
            tick_labels_.push_back(StringPrintf("%g", x));
        }
    }

    // The interval between two neighbor ticks.
    double interval_;

    // Position of ticks.
    std::vector<double> ticks_;

    // Labels for every tick.
    std::vector<std::string> tick_labels_;

    // True if the values are increasing.
    bool is_increasing_;

    DISALLOW_COPY_AND_ASSIGN(Axis);
};

} // namespace plot
} // namespace cl

#endif // VISUALIZATION_PLOT_AXIS_H_
