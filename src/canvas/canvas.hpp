#ifndef CANVAS_HPP
#define CANVAS_HPP

#include <vector>
#include "../object/obj.hpp"
#include "color.hpp"
#include <bits/stdc++.h> 

class canvas {
public:
  int WIDTH, HEIGHT, LINE_THICKNESS = 10;
  std::vector<std::vector<RGBA>> pix, ovrly;
  canvas(int w = 1280, int h = 720);
  void draw(Coord p, const RGBA &color);
  void draw(const Segment *seg, const RGBA &color);
  void draw(const Line *ln, const RGBA &color, bool permanent = 0);
  void draw(const Circle *cir, const RGBA &color);
  void drawChar(const Coord, char c, const RGBA &color, int scale = 1);
  void drawString(const Coord, string s, const RGBA &color, int scale = 1);

  void render(const char* filename);
};

#endif
