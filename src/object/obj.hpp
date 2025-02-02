#ifndef OBJECT
#define OBJECT

#include "./core/point.hpp"
#include "./core/line.hpp"

struct node : public point{
  vec2 v;

  node(float x = 0, float y = 0);
  vec2 loc() const override;
};

struct rotor : public point{
  float len, arg;
  point& origin;

  rotor(float l, point& p);
  vec2 loc() const override;

  void set_rot(float th);
};

#endif // !OBJECT
