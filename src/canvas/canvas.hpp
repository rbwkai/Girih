#ifndef CANVAS
#define CANVAS

#include <bits/stdc++.h> 
#include "../object/point.hpp"

using namespace std;
struct canvas{
  int SIZE, LINE_THICKNESS=2;
  std::vector<vector<int>> pix, ovl;
  canvas(int s = 1000);

  void draw(vec2 p);
  void visl(vec2 p);
  void render(const char* filename);
};

#endif // !CANVAS
