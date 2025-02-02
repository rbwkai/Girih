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




