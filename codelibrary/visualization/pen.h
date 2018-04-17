//
// Copyright 2015 Yangbin Lin. All Rights Reserved.
//
// Author: yblin.xmu@qq.com (Yangbin Lin)
//
// This file is part of the Code Library.
//

#ifndef VISUALIZATION_PEN_H_
#define VISUALIZATION_PEN_H_

#include "codelibrary/visualization/color.h"

namespace cl {

/// Pen for Visualization.
/**
 * The Pen class defines how a Painter should draw lines and outlines of shapes.
 */
class Pen {
public:
    /// Style of Pen.
    enum Style {
        SOLID_LINE    = 0,  // -----
        DASH_LINE     = 1,  // - - -
        DOT_LINE      = 2,  // . . .
        DASH_DOT_LINE = 3   // -.-.-
    };

    Pen(const RGB32Color& color = RGB32Color(0, 0, 0, 255),
        double width = 1.0,
        Style style = SOLID_LINE)
        : color_(color), width_(width), style_(style) {
        assert(width_ > 0.0);
    }

    double width() const {
        return width_;
    }

    void set_width(double width) {
        assert(width > 0.0);

        width_ = width;
    }

    const cl::RGB32Color& color() const {
        return color_;
    }

    void set_color(const cl::RGB32Color& color) {
        color_ = color;
    }

    const Style& style() const {
        return style_;
    }

    void set_style(Style style) {
        style_ = style;
    }

protected:
    RGB32Color color_; // Color of pen.
    double width_;     // Width of pen.
    Style style_;      // The pen style defines the line type.
};

} // namespace cl

#endif // VISUALIZATION_PEN_H_
