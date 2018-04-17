//
// Copyright 2015 Yangbin Lin. All Rights Reserved.
//
// Author: yblin.xmu@qq.com (Yangbin Lin)
//
// This file is part of the Code Library.
//

#ifndef VISUALIZATION_TERMINAL_SVG_TERMINAL_H_
#define VISUALIZATION_TERMINAL_SVG_TERMINAL_H_

#include <cassert>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "codelibrary/base/string_printf.h"
#include "codelibrary/visualization/terminal/terminal.h"

namespace cl {

/// SVG Termianl.
/**
 * Visualizing the figures on the Scalable Vector Graphics File.
 */
class SVGTerminal : public Terminal {
public:
    SVGTerminal(int height = 480, int width = 640)
        : Terminal(height, width) {
        font_.set_name("Times");
        Initialize();
    }

    /**
     * Clear the content of SVG.
     */
    virtual void clear() {
        content_.clear();
    }

    /**
     * Draw point (x, y).
     */
    virtual void DrawPoint(int x, int y) {
        content_ += ElementStart("circle") +
                    Attribute("cx", x) +
                    Attribute("cy", height_ - y) +
                    Attribute("r", pen_.width() * 0.5) +
                    Attribute("fill", ColorToString(pen_.color())) +
                    EmptyElementEnd();
    }

    /**
     * Draw line (x1, y1)->(x2, y2).
     */
    virtual void DrawLine(int x1, int y1, int x2, int y2) {
        content_ += ElementStart("line") +
                    Attribute("x1", x1) +
                    Attribute("y1", height_ - y1) +
                    Attribute("x2", x2) +
                    Attribute("y2", height_ - y2) +
                    LinePenAtribute() +
                    EmptyElementEnd();
    }

    /**
     * Draw polyline.
     */
    virtual void DrawPolyline(const std::vector<RPoint2D>& polyline) {
        std::string points;
        for (const RPoint2D& p : polyline) {
            points += StringPrintf("%g", p.x) + "," +
                      StringPrintf("%g", height_ - p.y) +
                      " ";
        }

        content_ += ElementStart("polyline") +
                    Attribute("fill", "none") +
                    LinePenAtribute() +
                    Attribute("points", points) +
                    EmptyElementEnd();
    }

    /**
     * Draw polygon.
     */
    virtual void DrawPolygon(const std::vector<RPoint2D>& polygon) {
        std::string points;
        for (const RPoint2D& p : polygon) {
            points += StringPrintf("%g", p.x) + "," +
                      StringPrintf("%g", height_ - p.y) +
                      " ";
        }

        content_ += ElementStart("polygon") +
                    Attribute("fill", ColorToString(pen_.color())) +
                    Attribute("fill-rule", "evenodd") +
                    Attribute("fill-opacity", pen_.color().alpha() / 255.0) +
                    Attribute("points", points) +
                    EmptyElementEnd();
    }

    /**
     * Draw text at position (x, y).
     */
    virtual void DrawText(int x, int y, const std::string& text) {
        y -= font_.size();

        // Escape SVG reserved characters.
        std::string trimmed_text;
        for (std::size_t i = 0; i < text.length(); ++i) {
            if (text[i] == '<') {
                trimmed_text += "&lt;";
            } else if (text[i] == '&') {
                if (text.length() > 2 && text[1] == '#' && text[2] == 'x')
                    trimmed_text += text[i];
                else
                    trimmed_text += "&amp;";
            } else {
                trimmed_text += text[i];
            }
        }

        std::string aligment;
        switch (font_.aligment()) {
        case Font::START:
            aligment = "start";
            break;
        case Font::END:
            aligment = "end";
            break;
        case Font::MIDDLE:
            aligment = "middle";
            break;
        }

        std::string font_weight = font_.bold() ? "bold" : "normal";

        content_ += ElementStart("text") +
                    Attribute("x", x) +
                    Attribute("y", height_ - y) +
                    Attribute("font-size", font_.size()) +
                    Attribute("text-anchor", aligment) +
                    Attribute("font-weight", font_weight) +
                    Attribute("font-family", font_.name()) + ">" +
                    trimmed_text +
                    ElementEnd("text");
    }

    /**
     * Save to the SVG file.
     */
    virtual void SaveToFile(const std::string& file) const {
        std::ofstream fout(file);
        fout << head_ << content_ << ElementEnd("svg");
    }

    /**
     * Resize the terminal.
     */
    virtual void Resize(int height, int width) {
        assert(height > 0 && width > 0);

        if (height_ == height && width_ == width) return;

        height_ = height;
        width_  = width;
        Initialize();
    }

private:
    /**
     * Convert a value into XML attribute.
     */
    template <typename T>
    static const std::string Attribute(const std::string& attribute_name,
                                       const T& value) {
        std::stringstream ss;
        ss << attribute_name << "=\"" << value << "\" ";
        return ss.str();
    }

    /**
     * @return a string that represents starting of a SVG element.
     */
    static const std::string ElementStart(const std::string& element_name) {
        return "\t<" + element_name + " ";
    }

    /**
     * @return a string that represents ending of a SVG element.
     */
    static const std::string ElementEnd(const std::string& element_name) {
        return "</" + element_name + ">\n";
    }

    /**
     * @return a string that represents empty ending of a SVG element.
     */
    static const std::string EmptyElementEnd() {
        return "/>\n";
    }

    /**
     * Convert the RGB Color into string.
     */
    static const std::string ColorToString(const cl::RGB32Color& c) {
        return "rgba(" + std::to_string(c.red()) + "," +
                         std::to_string(c.green()) + "," +
                         std::to_string(c.blue()) + "," +
                         std::to_string(c.alpha()) + ")";
    }

    /**
     * Initialize the SVG terminal.
     */
    void Initialize() {
        // Initialize the SVG header.
        head_ = "<?xml " + Attribute("version", "1.0") + "?>\n" +
                "<svg " +
                Attribute("xmlns", "http://www.w3.org/2000/svg") +
                Attribute("xmlns:xlink", "http://www.w3.org/1999/xlink") +
                Attribute("width",  width_) +
                Attribute("height", height_) +
                ">\n\n";
    }

    /**
     * Get the pen attribute for line drawing.
     */
    const std::string LinePenAtribute() const {
        std::string dash;
        switch (pen_.style()) {
        case Pen::SOLID_LINE:
            break;
        case Pen::DASH_LINE:
            dash = Attribute("stroke-dasharray", std::string("10,10"));
            break;
        case Pen::DOT_LINE:
            dash = Attribute("stroke-dasharray", std::string("2,2"));
            break;
        case Pen::DASH_DOT_LINE:
            dash = Attribute("stroke-dasharray", std::string("2,10,2"));
            break;
        default:
            break;
        }

        return Attribute("stroke", ColorToString(pen_.color())) +
               Attribute("stroke-width", pen_.width()) +
               dash;
    }

    std::string head_;    // SVG head.
    std::string content_; // SVG content.

    DISALLOW_COPY_AND_ASSIGN(SVGTerminal);
};

} // namespace cl

#endif // VISUALIZATION_TERMINAL_SVG_TERMINAL_H_
