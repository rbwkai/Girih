#ifndef POINT
#define POINT

struct vec2 {
  float x, y;
  vec2(float x = 0, float y = 0) : x(x), y(y) {}

  vec2 operator+(const vec2& other) const {
    return vec2(x + other.x, y + other.y);
  }
};

struct point {
  virtual ~point() = default;
  virtual vec2 loc() const = 0;
};

#endif // !POINT
