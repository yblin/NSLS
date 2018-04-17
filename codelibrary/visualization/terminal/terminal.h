//
// Copyright 2015 Yangbin Lin. All Rights Reserved.
//
// Author: yblin.xmu@qq.com (Yangbin Lin)
//
// This file is part of the Code Library.
//

#ifndef VISUALIZATION_TERMINAL_TERMINAL_H_
#define VISUALIZATION_TERMINAL_TERMINAL_H_

#include <string>
#include <vector>

#include "codelibrary/base/macros.h"
#include "codelibrary/geometry/kernel/point_2d.h"
#include "codelibrary/visualization/color.h"
#include "codelibrary/visualization/font.h"
#include "codelibrary/visualization/pen.h"

namespace cl {

/// Terminal for Visualization.
/**
 * The terminal class to perform low-level painting.
 */
class Terminal {
public:
    Terminal(int height = 480, int width = 640)
        : height_(height), width_(width) {
        assert(height_ >= 0 && width_ >= 0);
    }

    virtual ~Terminal() {}

    /**
     * Clear the painter.
     */
    virtual void clear() = 0;

    /**
     * Draw point (x, y).
     */
    virtual void DrawPoint(int x, int y) = 0;

    /**
     * Draw line (x1, y1)->(x2, y2).
     */
    virtual void DrawLine(int x1, int y1, int x2, int y2) = 0;

    /**
     * Draw polyline.
     */
    virtual void DrawPolyline(const std::vector<RPoint2D>& polyline) = 0;

    /**
     * Draw polygon.
     */
    virtual void DrawPolygon(const std::vector<RPoint2D>& polygon) = 0;

    /**
     * Draw text.
     */
    virtual void DrawText(int left_x, int top_y, const std::string& text) = 0;

    /**
     * Save to the file.
     */
    virtual void SaveToFile(const std::string& file) const = 0;

    /**
     * Resize the terminal.
     */
    virtual void Resize(int height, int width) = 0;

    /**
     * @return the height of terminal.
     */
    int height() const {
        return height_;
    }

    /**
     * @return the width of terminal.
     */
    int width() const {
        return width_;
    }

    /**
     * @return the current pen.
     */
    const Pen& pen() const {
        return pen_;
    }

    /**
     * Set the current pen.
     */
    void set_pen(const Pen& pen) {
        pen_ = pen;
    }

    /**
     * @return the current font.
     */
    const Font& font() const {
        return font_;
    }

    /**
     * Set font.
     */
    void set_font(const Font& font) {
        font_ = font;
    }

protected:
    int height_;       // The height of terminal.
    int width_;        // The width of terminal.
    Font font_;        // The font used for drawing text.
    Pen pen_;          // The current pen.

    DISALLOW_COPY_AND_ASSIGN(Terminal);
};

} // namespace cl

#endif // VISUALIZATION_TERMINAL_TERMINAL_H_
