#include <bits/stdc++.h>
#include "./obj.hpp"


//Point
node::node(float x, float y) : v(x, y){}
Coord node::loc() const {
  return v;
}


//Rotor
Rotor::Rotor(float l, Point& p) : len(l), arg(0),
                                  origin(p){}
Coord Rotor::loc() const {
  Coord ref = origin.loc();
  return Coord(ref.x + len*cos(arg), 
              ref.y + len*sin(arg));
}
void Rotor::set_rot(float th) {
  arg = th;
}


//Horizontal Line
HorizontalLine::HorizontalLine(Point& p) : ref(p) {}

l_eqn HorizontalLine::eqn() const {
  float y = ref.loc().y;
  return l_eqn(0, 1, -y);
}


//Perpendicular Line
PerpendicularLine::PerpendicularLine(Line& l, Point& p) : base(l), ref(p) {}

l_eqn PerpendicularLine::eqn() const {
  l_eqn base_eqn = base.eqn();
  float A = base_eqn.a;
  float B = base_eqn.b;
  auto pt = ref.loc();
  return l_eqn(B, -A, A * pt.y - B * pt.x);
}