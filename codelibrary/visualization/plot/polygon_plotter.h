//
// Copyright 2016 Yangbin Lin. All Rights Reserved.
//
// Author: yblin.xmu@qq.com (Yangbin Lin)
//
// This file is part of the Code Library.
//

#ifndef VISUALIZATION_PLOT_POLYGON_PLOTTER_H_
#define VISUALIZATION_PLOT_POLYGON_PLOTTER_H_

#include <vector>

#include "codelibrary/visualization/plot/point_plotter.h"

namespace cl {
namespace plot {

/// Polygon Plotter.
class PolygonPlotter : public PointPlotter {
public:
    explicit PolygonPlotter(const std::vector<RGB32Color>& color_map =
                            color_map::LINES)
        : PointPlotter(color_map) {}

    virtual ~PolygonPlotter() {}

    /**
     * Show the line plot on the given terminal within the given axes.
     *
     * @note that this function dose not update and draw the axes.
     */
    virtual void Show(const Axes* axes, Terminal* terminal) const {
        assert(axes);
        assert(terminal);

        if (empty()) return;

        // Draw polygons.
        for (std::size_t i = 0; i < data_.size(); ++i) {
            terminal->set_pen(pens_[i]);

            // Convert the coordinate for plotting.
            std::vector<RPoint2D> polygon;
            for (const RPoint2D& p : data_[i]) {
                const RPoint2D q = axes->ToUnitPlotPosition(p);
                polygon.emplace_back(q.x * terminal->width(),
                                     q.y * terminal->height());
            }
            terminal->DrawPolygon(polygon);
        }

        ShowTitle(axes, terminal);
    }

    /**
     * Show the polygon plot on the given terminal with the default XY axes.
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

#endif // VISUALIZATION_PLOT_POLYGON_PLOTTER_H_
