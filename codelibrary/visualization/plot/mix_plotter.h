//
// Copyright 2016 Yangbin Lin. All Rights Reserved.
//
// Author: yblin.xmu@qq.com (Yangbin Lin)
//
// This file is part of the Code Library.
//

#ifndef VISUALIZATION_PLOT_MIX_PLOTTER_H_
#define VISUALIZATION_PLOT_MIX_PLOTTER_H_

#include <memory>
#include <type_traits>
#include <vector>

#include "codelibrary/visualization/plot/axes.h"
#include "codelibrary/visualization/plot/plotter.h"

namespace cl {
namespace plot {

/// Mix Plotter.
/**
 * This class is used to plot several different plots on the same axes.
 *
 * Sample usage:
 *
 *   plot::MixPlotter plotter;
 *
 *   // Add plotters.
 *   plotter.AddPlotter(line_plotter);
 *   plotter.AddPlotter(scatter_plotter);
 *
 *   // Show.
 *   SVGTerminal terminal;
 *   plot::XYAxes axes;
 *   plotter.Show(&axes, &terminal);
 */
class MixPlotter {
public:
    MixPlotter()
        : font_("Times") {}

    /**
     * Clear the data.
     */
    void clear() {
        plotters_.clear();
        bounding_box_ = RBox2D();
    }

    /**
     * @return true if the plotter is empty.
     */
    bool empty() const {
        return plotters_.empty();
    }

    /**
     * Add a plotter, note that the plotter must be derived from class Plotter.
     */
    template <typename PlotterType>
    void AddPlotter(const PlotterType& plotter) {
        static_assert(std::is_base_of<Plotter, PlotterType>::value,
                      "The input parameter must be derived form Plotter");

        if (plotter.empty()) return;

        plotters_.push_back(std::make_shared<PlotterType>(plotter));
        bounding_box_.Union(plotter.bounding_box());
    }

    /**
     * Show multiple plots on the same axes.
     */
    void Show(Axes* axes, Terminal* terminal) {
        assert(axes);
        assert(terminal);

        terminal->clear();
        if (empty()) return;

        axes->Reset(bounding_box_);
        axes->Show(terminal);

        for (auto plotter : plotters_) {
            plotter->Show(axes, terminal);
        }

        ShowTitle(axes, terminal);
    }

    /**
     * @return the title of the plot.
     */
    const std::string& title() const {
        return title_;
    }

    /**
     * Set plot title.
     */
    void set_title(const std::string& title) {
        title_ = title;
    }

private:
    /**
     * Show the title on the terminal with the given axes.
     */
    void ShowTitle(const Axes* axes, Terminal* terminal) const {
        if (title_.empty()) return;

        // Show title.
        Font font = font_;
        font.set_aligment(Font::MIDDLE);
        font.set_size(font_.size() * 2);
        font.set_bold(true);
        terminal->set_font(font);
        terminal->DrawText((axes->plot_area().x_min() +
                            axes->plot_area().x_max()) * terminal->width() / 2,
                           terminal->height(),
                           title_);
    }

    // Plotters for plotting.
    std::vector<std::shared_ptr<Plotter> > plotters_;

    // Bounding box of plots.
    RBox2D bounding_box_;

    // Font to plot the title.
    Font font_;

    // Title of the mix plotter.
    std::string title_;

    DISALLOW_COPY_AND_ASSIGN(MixPlotter);
};

} // namespace plot
} // namespace cl

#endif // VISUALIZATION_PLOT_MIX_PLOTTER_H_
