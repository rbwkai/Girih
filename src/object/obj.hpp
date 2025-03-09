#ifndef OBJECT
#define OBJECT

#include "./core/point.hpp"
#include "./core/line.hpp"
#include "../param/parameter.hpp"
#include "../canvas/color.hpp"

struct Node : public Point{
  float x, y;
  Node(float x = 0, float y = 0, RGBA color = White);
  Coord loc() const override;
  Node operator-(const Node &other) const{
    return Node(x - other.x, y - other.y, color - other.color);
  }
  Node operator+(const Node &other) const{
    return Node(x + other.x, y + other.y, color + other.color);
  }
  Node operator*(float t) const{
    return Node(x * t, y * t, color * t);
  }
};

struct Rotor : public Point{
  float len, arg;
  Point& origin;

  Rotor(float l, Point& p, RGBA color = White);
  Coord loc() const override;

  void set_rot(float th);
};

struct HorizontalLine : public Line {
  Point& ref;
  HorizontalLine(Point& p, RGBA color = White);
  l_eqn eqn() const override;
};

struct VerticalLine : public Line{
  Point& ref;
  VerticalLine(Point& p, RGBA color = White);
  l_eqn eqn() const override;
};

struct PerpendicularLine : public Line {
  Line& base;
  Point& ref;
  PerpendicularLine(Line& l, Point& p, RGBA color = White);
  l_eqn eqn() const override;
};

struct IntersectionPoint : public Point{
  Line &l1, &l2;
  IntersectionPoint(Line &l1, Line &l2, RGBA color = White);
  Coord loc() const override;
};

// midPoint of two given Points 
struct MidPoint : public Point {
  Point& p1;
  Point& p2;
  MidPoint(Point& a, Point& b, RGBA color = White);
  
  Coord loc() const override;
};

// equidistant Points from two given Points and also form right-angle
struct Equidistant : public Point {
  Point& p1;
  Point& p2;
  
  Equidistant(Point& a, Point& b, RGBA color = White);
  
  Coord loc() const override;
};

// rotating p2 by pi/2 counter-clockwise having centre p1 
struct Rotation : public Point {
  Point& p1;
  Point& p2;
  
  Rotation(Point& a, Point& b, RGBA color = White);
  
  Coord loc() const override;
};

// perpendicular bisector
struct PerpendicularBisector : public Line {
  Point& p1;
  Point& p2;
  
  PerpendicularBisector(Point& a, Point& b, RGBA color = White);
  l_eqn eqn() const override;
};



// internal division 1:r  for two given Points 
struct InternalDivision : public Point {
  Point& p1;
  Point& p2;
  float ratio; // Ratio in the form 1:ratio
  
  InternalDivision(Point& a, Point& b, float r, RGBA color = White);
  
  Coord loc() const override;
};

// external division 1:r  for two given Points 
struct ExternalDivision : public Point {
  Point& p1;
  Point& p2;
  float ratio; // Ratio in the form 1:ratio
  
  ExternalDivision(Point& a, Point& b, float r, RGBA color = White);
  
  Coord loc() const override;
};

/// Circle  /////

struct Circle : public Drawable{
  Point &center;
  Value& radius;
  RGBA color;
  Circle(Point &center, Value& radius, RGBA color = White) : center(center), radius(radius), color(color) {}

};

//// Segment  ////


struct Segment : public Drawable{
  Point& st;
  Point& en;
  RGBA color;
  Segment(Point& s, Point& e, RGBA color = White) : st(s), en(e), color(color) {}
  Segment operator=(const Segment seg){
    st = seg.st, en = seg.en, color = seg.color;
    return *this;
  } 
  Point* start() const;
  Point* end() const;
};

struct ExternalTangent : public Drawable{
  Circle &c1, &c2;
  RGBA color;
  ExternalTangent(Circle &c1, Circle &c2, RGBA color = White);
  pair<Node, Node> loc() const;
};



#endif // !OBJECT
