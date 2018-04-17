//
// Copyright 2016 Yangbin Lin. All Rights Reserved.
//
// Author: yblin.xmu@qq.com (Yangbin Lin)
//
// This file is part of the Code Library.
//

#ifndef VISUALIZATION_PLOT_POINT_PLOTTER_H_
#define VISUALIZATION_PLOT_POINT_PLOTTER_H_

#include <vector>

#include "codelibrary/geometry/kernel/box_2d.h"
#include "codelibrary/geometry/kernel/point_2d.h"
#include "codelibrary/visualization/plot/plotter.h"
#include "codelibrary/visualization/plot/xy_axes.h"
#include "codelibrary/visualization/terminal/terminal.h"

namespace cl {
namespace plot {

/// 2D Point for Plotter.
/**
 * Sample usage:
 *
 *   // Genreate data.
 *   std::mt19937 random;
 *   RBox2D box(0.0, 1.0, 0.0, 1.0);
 *   geometry::RandomPointInBox2D random_point(box);
 *   std::vector<RPoint2D> points;
 *   for (int i = 0; i < 1000; ++i) {
 *       points.push_back(random_point(&random));
 *   }
 *
 *   // Draw and show the scatter.
 *   plot::PointPlotter point_plotter;
 *   point_plotter.Plot(points);
 *   SVGTerminal terminal;
 *   point_plotter.Show(&terminal);
 *
 *   // Save the plot to the file.
 *   terminal.SaveToFile("test.svg");
 */
class PointPlotter : public Plotter {
public:
    explicit PointPlotter(const std::vector<RGB32Color>& color_map =
                          color_map::PRISM)
        : Plotter(), color_map_(color_map) {
        assert(!color_map_.empty());
    }

    virtual ~PointPlotter() {}

    /**
     * Clear the data.
     */
    virtual void clear() {
        data_.clear();
        pens_.clear();
        bounding_box_ = RBox2D();
    }

    /**
     * @return true if the plotter is empty.
     */
    virtual bool empty() const {
        return data_.empty();
    }

    /**
     * Plot 2D points by a specific pen.
     */
    void Plot(const std::vector<RPoint2D>& points, const Pen& pen) {
        if (points.empty()) return;

        data_.push_back(points);
        pens_.push_back(pen);

        // Compute the bounding box of plot.
        RBox2D box(data_.back().begin(), data_.back().end());
        bounding_box_.Union(box);
    }

    /**
     * Plot Y versus the corresponding values in X by a specific pen.
     */
    template <typename T1, typename T2>
    void Plot(const std::vector<T1>& x, const std::vector<T2>& y,
              const Pen& pen) {
        assert(x.size() == y.size());

        std::vector<RPoint2D> points;
        for (std::size_t i = 0; i < x.size(); ++i) {
            points.emplace_back(static_cast<double>(x[i]),
                                static_cast<double>(y[i]));
        }
        Plot(points, pen);
    }

    /**
     * Plot Y versus the corresponding values in X.
     */
    template <typename T1, typename T2>
    void Plot(const std::vector<T1>& x, const std::vector<T2>& y) {
        Plot(x, y, CreatePen());
    }

    /**
     * Plot the given 2D points.
     */
    void Plot(const std::vector<RPoint2D>& points) {
        Plot(points, CreatePen());
    }

    /**
     * Show points on the given terminal within the given axes.
     *
     * @note that this function dose not update and draw the axes.
     */
    virtual void Show(const Axes* axes, Terminal* terminal) const {
        assert(axes);
        assert(terminal);

        if (empty()) return;

        // Draw points.
        for (std::size_t i = 0; i < data_.size(); ++i) {
            terminal->set_pen(pens_[i]);

            // Convert the coordinate for plotting.
            for (const RPoint2D& p : data_[i]) {
                const RPoint2D q = axes->ToUnitPlotPosition(p);
                terminal->DrawPoint(q.x * terminal->width(),
                                    q.y * terminal->height());
            }
        }

        ShowTitle(axes, terminal);
    }

    /**
     * Show the plot on the given terminal with the default XY axes.
     */
    virtual void Show(Terminal* terminal) const {
        assert(terminal);

        terminal->clear();
        if (empty()) return;

        XYAxes xy_axes(bounding_box_);
        xy_axes.Show(terminal);
        Show(&xy_axes, terminal);
    }

protected:
    /**
     * Create a new pen according to the given color map.
     */
    virtual const Pen CreatePen() const {
        return Pen(color_map_[pens_.size() % color_map_.size()], 2.0);
    }

    // Color map to draw the lines.
    const std::vector<RGB32Color>& color_map_;

    // The input data for plotting.
    std::vector<std::vector<RPoint2D> > data_;

    // The pens for each line.
    std::vector<Pen> pens_;
};

} // namespace plot
} // namespace cl

#endif // VISUALIZATION_PLOT_POINT_PLOTTER_H_
