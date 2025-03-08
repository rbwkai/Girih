#ifndef PARAM
#define PARAM

#include "../object/core/point.hpp"

struct length{
  virtual ~length() = default;
  virtual float len() const = 0;
};

struct proxim : public length{
  Point& a;
  Point& b;

  proxim(Point& a, Point& b);
  float len() const override;
};

#endif // !PARAM
