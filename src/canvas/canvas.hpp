#ifndef CANVAS_HPP
#define CANVAS_HPP

#include <vector>
#include "../object/obj.hpp"
#include "color.hpp"
#include <bits/stdc++.h> 

class canvas {
public:
  int WIDTH, HEIGHT, LINE_THICKNESS = 10;

  // Define the maximum distance for the kernel influence.
  // Adjust the sigma for smoother Gaussian falloff
  const float MAXDIS_PARAM = 9.0f;
  const float SIGMA_PARAM = 18.0f;
  const float maxDist = LINE_THICKNESS + MAXDIS_PARAM;
  const float sigma = maxDist / SIGMA_PARAM;
  const float inv2_sigma2 = -1.0f / (2.0 * sigma * sigma);
  
std::vector<std::vector<RGBA>> pix, ovrly;
  canvas(int w = 1280, int h = 720);
  void draw(Coord p, const RGBA &color, bool permanent = 1);
  void draw(const Segment *seg, const RGBA &color, bool parmaent = 0);
  void draw(const ExternalTangent *ext, const RGBA &color, bool parmaent = 0);
  void draw(const Line *ln, const RGBA &color, bool permanent = 0);
  void draw(const Circle *cir, const RGBA &color, bool parmanent = 0);
  void drawChar(const Coord, char c, const RGBA &color, int scale = 1, int permanent = 1);
  void drawString(const Coord, string s, const RGBA &color, int scale = 1, int permanent = 1);

  void render(const char* filename);
};

#endif
