#include <bits/stdc++.h>

#include <numbers>

#include "./anim/animate.hpp"
#include "./object/obj.hpp"
#include "./param/parameter.hpp"

using namespace std;

float pi = 3.1415927410125732421875;

int main() {
  canvas cnv(1024, 1024);

  Node ori(-200, 0);
  Node upleft(-100, -100);
  HorizontalLine x_axis(ori);
  cnv.draw(&x_axis, White, 1);

  VerticalLine y_axis(ori);
  cnv.draw(&y_axis, White, 1);

  cnv.drawString({0, 400}, "GIRIH RANDOM WAVE", Red, 2); 

  Rotor r1(30, ori, Maroon);
  Keyframe kff(r1.len, float(70), float(200));
  Keyframe kf_r1(r1.arg, float(0), 6 * pi);

  Segment sr(ori, r1);

  Node tm(0, 0);
  Keyframe kf_tm(tm.x, float(0), float(350));
  HorizontalLine H(r1);
  VerticalLine V(tm);

  IntersectionPoint I(H, V, Red);
  Segment seg(I, tm, Sapphire), seg2(I, r1, Rosewater);

  Keyframe kfc(I.color, Red, Blue);

  Node ntri(0, 0, Blue);
  Node rtri(350, -360, Red);
  Segment ss(ntri, rtri, Blue);
  Keyframe fk2(ntri, ntri, rtri);
  Keyframe fk1(rtri, rtri, ntri);

  Circle cir(I, 5, Red);

  vector<Keyframe*> keys = {&kf_r1, &kf_tm, &kfc, &fk1, &fk2, &kff};
  vector<Point*> objList = {&r1, &I};
  vector<Segment*> segList = {&sr, &seg, &seg2};
  vector<Line*> lineList = {};
  vector<Circle*> circleList = {
    &cir
  };

  animate(objList, segList, lineList, circleList, cnv, keys, 0);
}
