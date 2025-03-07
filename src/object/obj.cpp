#include <bits/stdc++.h>
#include "./obj.hpp"


//point
node::node(float x, float y) : v(x, y){}
vec2 node::loc() const {
  return v;
}


//rotor
rotor::rotor(float l, point& p) : len(l), arg(0),
                                  origin(p){}
vec2 rotor::loc() const {
  vec2 ref = origin.loc();
  return vec2(ref.x + len*cos(arg), 
              ref.y + len*sin(arg));
}
void rotor::set_rot(float th) {
  arg = th;
}


//Horizontal Line
HorizontalLine::HorizontalLine(point& p) : ref(p) {}

l_eqn HorizontalLine::eqn() const {
  float y = ref.loc().y;
  return l_eqn(0, 1, -y);
}


//Perpendicular Line
PerpendicularLine::PerpendicularLine(line& l, point& p) : base(l), ref(p) {}

l_eqn PerpendicularLine::eqn() const {
  l_eqn base_eqn = base.eqn();
  float A = base_eqn.a;
  float B = base_eqn.b;
  auto pt = ref.loc();
  return l_eqn(B, -A, A * pt.y - B * pt.x);
}