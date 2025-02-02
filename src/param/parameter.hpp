#ifndef PARAM
#define PARAM

#include "../object/core/point.hpp"

struct length{
  virtual ~length() = default;
  virtual float len() const = 0;
};

struct proxim : public length{
  point& a;
  point& b;

  proxim(point& a, point& b);
  float len() const override;
};

#endif // !PARAM
