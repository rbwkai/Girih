#include <bits/stdc++.h> 

#include "./object/obj.hpp"
#include "./param/parameter.hpp"
#include "./anim/animate.hpp"

using namespace std;

float pi = std::numbers::pi;
int main(){
  canvas cnv;

  node ori(-50, 0);

  rotor r1(170, ori); Keyframe kf1(r1.arg, (float)0, 2*pi);
  rotor r2(100, r1); Keyframe kf2(r2.arg, float(0), 3 * pi);
  segment s1(ori, r1), s2(r1, r2); 
  HorizontalLine H(r1);
  PerpendicularLine P(H, r2);

  RGBA red(255, 0, 0, 255);
  RGBA blue(0, 0, 255, 255);
  RGBA pen; Keyframe kfc(pen, red, blue);

  vector<Keyframe> keys = {
    kf1, kf2, kfc
  };
  vector<point*> objList = {
    &r1, &r2
  };
  
  vector<segment*> segList = {
    &s1, &s2
  };
  
  vector<line*> lineList = {
    &H, &P
  };

  animate(objList, segList, lineList, cnv, pen, keys, 0);
}
