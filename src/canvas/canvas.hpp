#ifndef CANVAS_HPP
#define CANVAS_HPP

#include <vector>
#include "../object/obj.hpp"

#include <bits/stdc++.h> 

using namespace std;
struct RGBA {
  unsigned char r, g, b, a;
  RGBA() : r(255), g(255), b(255), a(255) {} // default to opaque white
  RGBA(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a)
      : r(_r), g(_g), b(_b), a(_a) {}
};

class canvas {
public:
  int SIZE, LINE_THICKNESS=2;
  std::vector<std::vector<RGBA>> pix;

  canvas(int s = 1000);
  void draw(vec2 p, const RGBA &color);
  void visl(vec2 p);
  void render(const char* filename);
};

#endif
