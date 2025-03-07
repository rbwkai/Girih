#ifndef POINT
#define POINT

struct Coord {
  float x, y;
  Coord(float x = 0, float y = 0) : x(x), y(y) {}

  Coord operator+(const Coord& other) const {
    return Coord(x + other.x, y + other.y);
  }
};

struct Point {
  virtual ~Point() = default;
  virtual Coord loc() const = 0;
};

#endif // !POINT
