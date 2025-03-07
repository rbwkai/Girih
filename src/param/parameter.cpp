
#include <bits/stdc++.h>
#include "parameter.hpp"

//proxim
proxim::proxim(Point& a, Point&b) : a(a), b(b) {}
float proxim::len() const {
  Coord al = a.loc();
  Coord bl = b.loc();

  float dx = al.x - bl.x;
  float dy = al.y - bl.y;
  return sqrt(dx*dx + dy*dy);
}
