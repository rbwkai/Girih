#ifndef LINE
#define LINE

#include "drawable.hpp"

struct l_eqn {
  float a, b, c;
  l_eqn(float a, float b, float c) : a(a), b(b), c(c) {}
};

struct Line : public Drawable{ 
  RGBA color;
  Line(RGBA color) : color(color) {}
  virtual l_eqn eqn() const = 0;
};

#endif // !LINE
