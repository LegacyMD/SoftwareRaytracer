#pragma once

#include <stdint.h>

struct Color {
    float r, g, b;
    Color(float r, float g, float b) : r(r), g(g), b(b) {}

    static Color mix(const Color &c1, const Color &c2) {
        return Color{c1.r * c2.r, c1.g * c2.g, c1.b * c2.b};
    }

    Color &scale(float factor) {
        r *= factor;
        g *= factor;
        b *= factor;
        return *this;
    }

    static Color black() { return Color{0, 0, 0}; }
    static Color lightGray() { return Color{0.8f, 0.8f, 0.8f}; }
    static Color white() { return Color{1, 1, 1}; }
    static Color red() { return Color{1, 0, 0}; }
    static Color green() { return Color{0, 1, 0}; }
    static Color blue() { return Color{0, 0, 1}; }
    static Color yellow() { return Color{1, 1, 0}; }
};
