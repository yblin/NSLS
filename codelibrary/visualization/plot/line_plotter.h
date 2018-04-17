//
// Copyright 2016 Yangbin Lin. All Rights Reserved.
//
// Author: yblin.xmu@qq.com (Yangbin Lin)
//
// This file is part of the Code Library.
//

#ifndef VISUALIZATION_PLOT_LINE_PLOTTER_H_
#define VISUALIZATION_PLOT_LINE_PLOTTER_H_

#include <vector>

#include "codelibrary/visualization/plot/point_plotter.h"

namespace cl {
namespace plot {

/// 2D Line plotter.
/**
 * Sample usage:
 *
 *   // Input data.
 *   std::vector<double> x(100), y1(100), y2(100);
 *   for (int i = 0; i < 100; ++i) {
 *       x[i] = 2.0 * PI * i / 100.0;
 *       y1[i] = std::sin(x[i]);
 *       y2[i] = std::cos(x[i]);
 *   }
 *
 *   // Plotting.
 *   plot::LinePlotter line_plotter;
 *   line_plotter.Plot(x, y1);
 *   line_plotter.Plot(x, y2);
 *
 *   // Show the plot.
 *   SVGTerminal terminal;
 *   line_plotter.Show(&terminal);
 *
 *   // Save the plot to the file.
 *   terminal.SaveToFile("test.svg");
 */
class LinePlotter : public PointPlotter {
public:
    explicit LinePlotter(const std::vector<RGB32Color>& color_map =
                         color_map::LINES)
        : PointPlotter(color_map) {}

    virtual ~LinePlotter() {}

    /**
     * Show the line plot on the given terminal within the given axes.
     *
     * @note that this function dose not update and draw the axes.
     */
    virtual void Show(const Axes* axes, Terminal* terminal) const {
        assert(axes);
        assert(terminal);

        if (empty()) return;

        // Draw ploylines.
        for (std::size_t i = 0; i < data_.size(); ++i) {
            terminal->set_pen(pens_[i]);

            // Convert the coordinate for plotting.
            std::vector<RPoint2D> polyline;
            for (const RPoint2D& p : data_[i]) {
                const RPoint2D q = axes->ToUnitPlotPosition(p);
                polyline.emplace_back(q.x * terminal->width(),
                                      q.y * terminal->height());
            }
            terminal->DrawPolyline(polyline);
        }

        ShowTitle(axes, terminal);
    }

    /**
     * Show the line plot on the given terminal with the default XY axes.
     */
    virtual void Show(Terminal* terminal) const {
        assert(terminal);

        terminal->clear();
        if (empty()) return;

        XYAxes xy_axes(bounding_box_);
        xy_axes.Show(terminal);
        Show(&xy_axes, terminal);
    }
};

} // namespace plot
} // namespace cl

#endif // VISUALIZATION_PLOT_LINE_PLOTTER_H_
