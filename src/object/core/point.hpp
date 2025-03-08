#ifndef POINT
#define POINT

#include "../../canvas/color.hpp"

struct Coord {
  float x, y;
  Coord(float x = 0, float y = 0) : x(x), y(y) {}

  Coord operator+(const Coord& other) const {
    return Coord(x + other.x, y + other.y);
  }
  
};

struct Point {
  RGBA color;
  Point(RGBA color) : color(color) {}
  virtual ~Point() = default;
  virtual Coord loc() const = 0;
};


#endif // !POINT
