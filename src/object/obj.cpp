#include "./obj.hpp"

#include <bits/stdc++.h>

// Point
Node::Node(float x, float y, RGBA color) : x(x), y(y), Point(color) {}
Coord Node::loc() const { return Coord(x, y); }

// Rotor
Rotor::Rotor(float l, Point& p, RGBA color)
    : len(l), arg(0), origin(p), Point(color) {}
Coord Rotor::loc() const {
  Coord ref = origin.loc();
  return Coord(ref.x + len * cos(arg), ref.y + len * sin(arg));
}
void Rotor::set_rot(float th) { arg = th; }

IntersectionPoint::IntersectionPoint(Line& l1, Line& l2, RGBA color)
    : l1(l1), l2(l2), Point(color) {}

Coord IntersectionPoint::loc() const {
  auto [a1, b1, c1] = l1.eqn();
  auto [a2, b2, c2] = l2.eqn();
  float determinant = a1 * b2 - a2 * b1;

  if (determinant == 0) {
    std::cerr << "The lines are parallel or coincident, no unique intersection."
              << std::endl;
    exit(0);
  }

  float x = (b2 * (-c1) - b1 * (-c2)) / determinant;
  float y = (a1 * (-c2) - a2 * (-c1)) / determinant;
  return Coord(x, y);
}


InternalDivision::InternalDivision(Point& a, Point& b, float r, RGBA color)
    : p1(a), p2(b), ratio(r), Point(color) {}

Coord InternalDivision::loc() const {
  float m = 1.0f;
  float n = ratio;

  float x = (m * p2.loc().x + n * p1.loc().x) / (m + n);
  float y = (m * p2.loc().y + n * p1.loc().y) / (m + n);

  return Coord(x, y);
}

ExternalDivision::ExternalDivision(Point& a, Point& b, float r, RGBA color)
    : p1(a), p2(b), ratio(r), Point(color) {}

Coord ExternalDivision::loc() const {
  float m = 1.0f;
  float n = ratio;

  float x = (m * p2.loc().x - n * p1.loc().x) / (m - n);
  float y = (m * p2.loc().y - n * p1.loc().y) / (m - n);

  return Coord(x, y);
}


MidPoint::MidPoint(Point& a, Point& b, RGBA color) : p1(a), p2(b), Point(color) {}

Coord MidPoint::loc() const {
  return Coord((p1.loc().x + p2.loc().x) / 2, (p1.loc().y + p2.loc().y) / 2);
}

Equidistant::Equidistant(Point& a, Point& b, RGBA color) : p1(a), p2(b), Point(color) {}

Coord Equidistant::loc() const {
  // Compute the midPoint
  float mid_x = (p1.loc().x + p2.loc().x) / 2;
  float mid_y = (p1.loc().y + p2.loc().y) / 2;

  // Compute differences
  float dx = p2.loc().x - p1.loc().x;
  float dy = p2.loc().y - p1.loc().y;

  // Compute the equidistant right-angle Point
  float equi_x = mid_x - dy / 2;
  float equi_y = mid_y + dx / 2;

  return Coord(equi_x, equi_y);
}

Rotation::Rotation(Point& a, Point& b, RGBA color)
    : p1(a), p2(b), Point(color) {}

Coord Rotation::loc() const {
  Coord center = p1.loc();
  Coord pt = p2.loc();

  float dx = pt.x - center.x;
  float dy = pt.y - center.y;

  return Coord(center.x - dy, center.y + dx);
}



////////////----     Line Starts here     ---------///////////////

// Horizontal Line
HorizontalLine::HorizontalLine(Point& p, RGBA color) : ref(p), Line(color) {}

l_eqn HorizontalLine::eqn() const {
  float y = ref.loc().y;
  return l_eqn(0, 1, -y);
}

VerticalLine::VerticalLine(Point& p, RGBA color) : ref(p), Line(color) {}

l_eqn VerticalLine::eqn() const {
  float x = ref.loc().x;
  return l_eqn(1, 0, -x);
}

// Perpendicular Line
PerpendicularLine::PerpendicularLine(Line& l, Point& p, RGBA color)
    : base(l), ref(p), Line(color) {}

l_eqn PerpendicularLine::eqn() const {
  l_eqn base_eqn = base.eqn();
  float A = base_eqn.a;
  float B = base_eqn.b;
  auto pt = ref.loc();
  return l_eqn(B, -A, A * pt.y - B * pt.x);
}


PerpendicularBisector::PerpendicularBisector(Point& a, Point& b, RGBA color)
    : p1(a), p2(b), Line(color) {}

l_eqn PerpendicularBisector::eqn() const {
  float mid_x = (p1.loc().x + p2.loc().x) / 2;
  float mid_y = (p1.loc().y + p2.loc().y) / 2;

  float dx = p2.loc().x - p1.loc().x;
  float dy = p2.loc().y - p1.loc().y;
  
  float a = dx;
  float b = dy;
  float c = -(a * mid_x + b * mid_y);

  return l_eqn(a, b, c);
}



//Segment

Point* Segment::start() const{
  return &st;
}

Point* Segment::end() const{
  return &en;
}

ExternalTangent::ExternalTangent(Circle &c1, Circle &c2, RGBA color) : c1(c1), c2(c2), color(color){}

pair<Node, Node> ExternalTangent::loc() const{
  auto [x1, y1] = c1.center.loc();
  float r1 = c1.radius.val();
  auto [x2, y2] = c2.center.loc();
  float r2 = c2.radius.val();
  
  float dx = x2 - x1;
  float dy = y2 - y1;
  float d = sqrt(dx * dx + dy * dy);
  
  float scale1 = r1 / d;
  float scale2 = r2 / d;
  
  Node P1 = {x1 + scale1 * dx, y1 + scale1 * dy};
  Node P2 = {x2 - scale2 * dx, y2 - scale2 * dy};
  return {P1, P2};
}
