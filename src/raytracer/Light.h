#pragma once

#include "util/Vector.h"
#include "util/Color.h"

class Light {
  public:
    Light(const Vec3f &position, const Color &color) : position(position), color(color) {}

    const Vec3f &getPosition() const { return position; }
    const Color &getColor() const { return color; }

  private:
    Vec3f position;
    Color color;
};
