#ifndef OBJECT
#define OBJECT

#include "./core/point.hpp"
#include "./core/line.hpp"

struct node : public Point{
  Coord v;

  node(float x = 0, float y = 0);
  Coord loc() const override;
};

struct Rotor : public Point{
  float len, arg;
  Point& origin;

  Rotor(float l, Point& p);
  Coord loc() const override;

  void set_rot(float th);
};

struct HorizontalLine : public Line {
  Point& ref;
  HorizontalLine(Point& p);
  l_eqn eqn() const override;
};

struct PerpendicularLine : public Line {
  Line& base;
  Point& ref;
  PerpendicularLine(Line& l, Point& p);
  l_eqn eqn() const override;
};

struct Intersection : public Point{

};

#endif // !OBJECT
