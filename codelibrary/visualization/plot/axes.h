//
// Copyright 2016 Yangbin Lin. All Rights Reserved.
//
// Author: yblin.xmu@qq.com (Yangbin Lin)
//
// This file is part of the Code Library.
//

#ifndef VISUALIZATION_PLOT_AXES_H_
#define VISUALIZATION_PLOT_AXES_H_

#include <cassert>

#include "codelibrary/base/macros.h"
#include "codelibrary/geometry/kernel/box_2d.h"
#include "codelibrary/geometry/kernel/point_2d.h"
#include "codelibrary/visualization/terminal/terminal.h"

namespace cl {
namespace plot {

/// Baisc 2D Axes for Plot.
class Axes {
public:
    Axes()
        : font_("Times"),
          plot_area_(0.1, 0.9, 0.1, 0.9),
          visibility_(true) {}

    virtual ~Axes() {}

    /**
     * Reset this axis.
     */
    virtual void Reset(const RBox2D& box, int max_ticks = 10) = 0;

    /**
     * Show this axis on the given terminal.
     */
    virtual void Show(Terminal* terminal) const = 0;

    /**
     * @return the bounding box of the axes.
     */
    virtual const RBox2D bounding_box() const = 0;

    /**
     * Convert the axis point to the unit normalized plot position.
     */
    virtual const RPoint2D ToUnitPlotPosition(const RPoint2D& p) const = 0;

    /**
     * Set defulat pen to plot the axis lines.
     */
    void set_pen(const Pen& pen) {
        pen_ = pen;
    }

    /**
     * Set default font to plot the axis labels.
     */
    void set_font(const Font& font) {
        font_ = font;
    }

    /**
     * @return the position of the axes within the plot.
     */
    const RBox2D& plot_area() const {
        return plot_area_;
    }

    /**
     * Set visibility for the axes.
     */
    void set_visibility(bool is_visible) {
        visibility_ = is_visible;
    }

    /**
     * @return the visibility of the axes.
     */
    bool visibility() const {
        return visibility_;
    }

protected:
    // Pen to plot the axes lines.
    Pen pen_;

    // Font to plot the axes labels.
    Font font_;

    // The position of the axes within the plot.
    // The values are measured in unites normalized to the container.
    RBox2D plot_area_;

    // True if the axes is visible.
    bool visibility_;

private:
    DISALLOW_COPY_AND_ASSIGN(Axes);
};

} // namespace plot
} // namespace cl

#endif // VISUALIZATION_PLOT_AXES_H_
