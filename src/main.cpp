#include <bits/stdc++.h> 

#include "./object/obj.hpp"
#include "./param/parameter.hpp"
#include "./anim/animate.hpp"
#include <numbers>

using namespace std;

float pi = 3.1415927410125732421875;

int main(){
  canvas cnv(1024);

  Node ori(0, 0);
  Rotor r1(300, ori); Keyframe kf1(r1.arg, float(0), 4 * pi);
  Rotor r2(50, r1, Red);   Keyframe kf2(r2.arg, float(0), 9 * pi);
  Rotor r3(150, ori); Keyframe kf3(r3.arg, float(0), 4 * pi);
  Rotor r4(50, r3);   Keyframe kf4(r4.arg, float(0), 8 * pi);
  Circle cir(r1, float(50), Lavender);
  Keyframe kf5(cir.radius, float(50), float(100));
  segment seg1(r1, r2), seg2(r3, r4);

  Keyframe kfc1(cir.color, Blue, Red);
  // Keyframe kfc2()
  vector<Keyframe*> keys = {
    &kf1, &kf2, &kf3, &kf4, &kf5, &kfc1
  };
  vector<Point*> objList = {
    &r1, &r2, &r3, &r4
  };
  
  vector<segment*> segList = {
    &seg1, &seg2
  };
    
  vector<Line*> lineList = {
    
  };

  vector<Circle*> circleList = {
    &cir
  };

  animate(objList, segList, lineList, circleList, cnv, keys, 0);
}
