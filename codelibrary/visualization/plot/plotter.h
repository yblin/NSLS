//
// Copyright 2016 Yangbin Lin. All Rights Reserved.
//
// Author: yblin.xmu@qq.com (Yangbin Lin)
//
// This file is part of the Code Library.
//

#ifndef VISUALIZATION_PLOT_PLOTTER_H_
#define VISUALIZATION_PLOT_PLOTTER_H_

#include <vector>

#include "codelibrary/geometry/kernel/box_2d.h"
#include "codelibrary/visualization/plot/axes.h"
#include "codelibrary/visualization/terminal/terminal.h"

namespace cl {
namespace plot {

/// Basic 2D plotter.
/**
 * This plotter is used to plot the 2D geometric objects.
 */
class Plotter {
public:
    Plotter()
        : font_("Times") {}

    virtual ~Plotter() {}

    /**
     * Clear the data.
     */
    virtual void clear() = 0;

    /**
     * @return true if the plotter is empty.
     */
    virtual bool empty() const = 0;

    /**
     * Show the plot on the given terminal within the given axes.
     *
     * @note that this function dose not update and draw the axes.
     */
    virtual void Show(const Axes* axes, Terminal* terminal) const = 0;

    /**
     * Show the line plot on the given terminal with the default XY axes.
     */
    virtual void Show(Terminal* terminal) const = 0;

    /**
     * @return the bounding box of the input data.
     */
    const RBox2D& bounding_box() const {
        return bounding_box_;
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

protected:
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

    // Bounding box of input data.
    RBox2D bounding_box_;

    // Font to plot the title.
    Font font_;

    // Tht title of plotter.
    std::string title_;
};

} // namespace plot
} // namespace cl

#endif // VISUALIZATION_PLOT_PLOTTER_H_
