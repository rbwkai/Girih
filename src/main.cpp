#include <bits/stdc++.h>

#include "./anim/animate.hpp"
#include "./object/obj.hpp"
#include "./param/parameter.hpp"

using namespace std;

float pi = 3.1415927410125732421875;

int main() {
  canvas cnv(1024, 1024);

  Node ori(-200, 0);

  HorizontalLine x_axis(ori);
  cnv.draw(&x_axis, White, 1);

  VerticalLine y_axis(ori);
  cnv.draw(&y_axis, White, 1);


  Rotor r1(100, ori, Maroon);
  Keyframe kf_r1(r1.arg, float(0), 2 * pi);

  Segment sr(ori, r1);

  HorizontalLine H(r1);

  Node tm(0, 0);
  Keyframe kf_tm(tm.x, float(0), float(350));
  VerticalLine V(tm);

  IntersectionPoint I(H, V, Red);

  Segment seg(I, tm, Sapphire);
  Segment seg2(I, r1, Rosewater);

  Keyframe kfc(I.color, Red, Blue);
  PointLineDistance v_sine(r1, x_axis, "Height: ");


vector<Point*> objList = {&r1, &I};
vector<Segment*> segList = {&sr, &seg, &seg2};
vector<Line*> lineList = {};
vector<Circle*> circleList = {};
vector<Keyframe*> keys = {&kf_r1, &kf_tm, &kfc};


animate(objList, segList, lineList,
        circleList, v_sine, cnv, keys, 0);

}
