//
// Copyright 2016 Yangbin Lin. All Rights Reserved.
//
// Author: yblin.xmu@qq.com (Yangbin Lin)
//
// This file is part of the Code Library.
//

#ifndef VISUALIZATION_PLOT_XY_AXES_H_
#define VISUALIZATION_PLOT_XY_AXES_H_

#include <cassert>
#include <string>

#include "codelibrary/base/macros.h"
#include "codelibrary/visualization/plot/axis.h"
#include "codelibrary/visualization/plot/axes.h"

namespace cl {
namespace plot {

/// XY Axes for Plot.
class XYAxes : public Axes {
public:
    XYAxes() : Axes() {}

    explicit XYAxes(const RBox2D& box)
        : Axes() {
        assert(!box.empty());

        Reset(box);
    }

    /**
     * Reset this axis.
     */
    virtual void Reset(const RBox2D& box, int max_ticks = 10) {
        assert(!box.empty());

        x_axis_.Reset(box.x_min(), box.x_max(), max_ticks);
        y_axis_.Reset(box.y_min(), box.y_max(), max_ticks);
    }

    /**
     * Show this axis on the given terminal.
     */
    virtual void Show(Terminal* terminal) const {
        assert(terminal);

        if (!visibility_) return;

        // The tick length: default is 5.0 (5 pixels).
        const double tick_length = 5.0;

        // Set terminal pen and font.
        terminal->set_pen(pen_);
        Font font = font_;

        // Draw X axis.
        font.set_aligment(Font::MIDDLE);
        terminal->set_font(font);

        // Draw ticks and labels.
        for (std::size_t i = 0; i < x_axis_.ticks().size(); ++i) {
            const std::string& label = x_axis_.tick_labels()[i];
            double x = ToXPlotPosition(x_axis_.ticks()[i]) *
                       terminal->width();

            // The Y position of tick on the axis.
            double tick = plot_area_.y_min() * terminal->height();

            // The Y position of mirror tick on the axis.
            double mirror_tick = plot_area_.y_max() * terminal->height();

            terminal->DrawLine(x, tick, x, tick + tick_length);
            terminal->DrawLine(x, mirror_tick,
                               x, mirror_tick - tick_length);
            terminal->DrawText(x, tick, label);
        }

        // Draw X axis lines.
        terminal->DrawLine(plot_area_.x_min() * terminal->width(),
                           plot_area_.y_min() * terminal->height(),
                           plot_area_.x_max() * terminal->width(),
                           plot_area_.y_min() * terminal->height());
        terminal->DrawLine(plot_area_.x_min() * terminal->width(),
                           plot_area_.y_max() * terminal->height(),
                           plot_area_.x_max() * terminal->width(),
                           plot_area_.y_max() * terminal->height());

        // Draw horizonal axis.
        font.set_aligment(Font::END);
        terminal->set_font(font);

        // Adjust the label position.
        const double label_y_shift = font.size() * 0.75;
        const double label_x_shift = 5.0;

        // Draw Y ticks and labels.
        for (std::size_t i = 0; i < y_axis_.ticks().size(); ++i) {
            const std::string& label = y_axis_.tick_labels()[i];
            double y = ToYPlotPosition(y_axis_.ticks()[i]) *
                       terminal->height();

            // The X position of tick on the axis.
            double tick = plot_area_.x_min() * terminal->width();

            // The X position of mirror tick on the axis.
            double mirror_tick = plot_area_.x_max() * terminal->width();

            terminal->DrawLine(tick, y, tick + tick_length, y);
            terminal->DrawLine(mirror_tick, y,
                               mirror_tick - tick_length, y);
            terminal->DrawText(tick - label_x_shift, y + label_y_shift,
                               label);
        }

        // Draw axis line.
        terminal->DrawLine(plot_area_.x_min() * terminal->width(),
                           plot_area_.y_min() * terminal->height(),
                           plot_area_.x_min() * terminal->width(),
                           plot_area_.y_max() * terminal->height());
        terminal->DrawLine(plot_area_.x_max() * terminal->width(),
                           plot_area_.y_min() * terminal->height(),
                           plot_area_.x_max() * terminal->width(),
                           plot_area_.y_max() * terminal->height());
    }

    /**
     * @return the bounding box of the axes values.
     */
    virtual const RBox2D bounding_box() const {
        return RBox2D(x_axis_.min(), x_axis_.max(),
                      y_axis_.min(), y_axis_.max());
    }

    /**
     * Convert the axis point to the unit normalized plot position.
     */
    virtual const RPoint2D ToUnitPlotPosition(const RPoint2D& p) const {
        return RPoint2D(ToXPlotPosition(p.x), ToYPlotPosition(p.y));
    }

    /**
     * Convert the value to the X plot position.
     */
    double ToXPlotPosition(double value) const {
        assert(value >= x_axis_.min() && value <= x_axis_.max());

        if (plot_area_.x_min() == plot_area_.x_max()) return 0.0;
        if (x_axis_.min() == x_axis_.max()) return 0.0;

        double plot_length = plot_area_.x_length();
        if (x_axis_.is_increasing()) {
            return (value - x_axis_.min()) / x_axis_.length() * plot_length +
                   plot_area_.x_min();
        } else {
            return (x_axis_.max() - value) / x_axis_.length() * plot_length +
                   plot_area_.x_min();
        }
    }

    /**
     * Convert the value to the Y plot position.
     */
    double ToYPlotPosition(double value) const {
        assert(value >= y_axis_.min() && value <= y_axis_.max());

        if (plot_area_.y_min() == plot_area_.y_max()) return 0.0;
        if (y_axis_.min() == y_axis_.max()) return 0.0;

        double plot_length = plot_area_.y_length();
        if (x_axis_.is_increasing()) {
            return (value - y_axis_.min()) / y_axis_.length() * plot_length +
                   plot_area_.y_min();
        } else {
            return (y_axis_.max() - value) / y_axis_.length() * plot_length +
                   plot_area_.y_min();
        }
    }

protected:
    // X and Y axis.
    Axis x_axis_, y_axis_;

    DISALLOW_COPY_AND_ASSIGN(XYAxes);
};

} // namespace plot
} // namespace cl

#endif // VISUALIZATION_PLOT_XY_AXES_H_
