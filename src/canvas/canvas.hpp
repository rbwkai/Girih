#ifndef CANVAS_HPP
#define CANVAS_HPP

#include <vector>
#include "../object/obj.hpp"
#include "color.hpp"
#include <bits/stdc++.h> 




class canvas {
public:
  int SIZE, LINE_THICKNESS = 2;
  std::vector<std::vector<RGBA>> pix, ovrly;
  canvas(int s = 1000);
  void draw(Coord p, const RGBA &color);
  void draw_segment(const segment *seg, const RGBA &color);
  void draw_line(const Line *ln, const RGBA &color, bool permanent = 0);
  void draw_circle(const Circle *cir, const RGBA &color);
  void render(const char* filename);
};

#endif
