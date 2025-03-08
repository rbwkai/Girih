#include <bits/stdc++.h>

#include <numbers>

#include "./anim/animate.hpp"
#include "./object/obj.hpp"
#include "./param/parameter.hpp"

using namespace std;

float pi = 3.1415927410125732421875;

int main() {
  canvas cnv(1024);

  Node ori(-200, 0);

  HorizontalLine x_axis(ori);
  cnv.draw_line(&x_axis, White, 1);

  VerticalLine y_axis(ori);
  cnv.draw_line(&y_axis, White, 1);

  Rotor r1(120, ori, Maroon);
  Keyframe kf_r1(r1.arg, float(0), 2 * pi);

  segment sr(ori, r1);

  Node tm(0, 0);
  Keyframe kf_tm(tm.x, float(0), float(350));
  HorizontalLine H(r1);
  VerticalLine V(tm);

  IntersectionPoint I(H, V, Red);
  segment seg(I, tm, Sapphire), seg2(I, r1, Rosewater);

  Keyframe kfc(I.color, Red, Blue);
  vector<Keyframe*> keys = {&kf_r1, &kf_tm, &kfc};
  vector<Point*> objList = {&r1, &I};
  vector<segment*> segList = {&sr, &seg, &seg2};
  vector<Line*> lineList = {};
  vector<Circle*> circleList = {

  };

  animate(objList, segList, lineList, circleList, cnv, keys, 0);
}
