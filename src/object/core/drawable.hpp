#ifndef DRAWABLE
#define DRAWABLE
#include "../../canvas/color.hpp"

struct Drawable{
    RGBA color;
    // Drawable(RGBA color) : color(color) {}
    virtual ~Drawable() = default;
};

#endif