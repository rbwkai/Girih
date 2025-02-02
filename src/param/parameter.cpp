
#include <bits/stdc++.h>
#include "parameter.hpp"

//proxim
proxim::proxim(point& a, point&b) : a(a), b(b) {}
float proxim::len() const {
  vec2 al = a.loc();
  vec2 bl = b.loc();

  float dx = al.x - bl.x;
  float dy = al.y - bl.y;
  return sqrt(dx*dx + dy*dy);
}
