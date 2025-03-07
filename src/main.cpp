#include <bits/stdc++.h> 

#include "./object/obj.hpp"
#include "./param/parameter.hpp"
#include "./anim/animate.hpp"

using namespace std;

float pi = std::numbers::pi;
int main(){
  canvas cnv;

  node ori;

  rotor r1(250, ori); Keyframe kf1(r1.arg, (float)0, 2*pi);

  segment s1(ori, r1);

  RGBA red(255, 0, 0, 255);
  RGBA blue(0, 0, 255, 255);
  RGBA pen; Keyframe kfc(pen, red, blue);

  vector<Keyframe> keys = {
    kf1, kfc
  };
  
  animate(r1, s1, cnv, pen, keys, 0);
}
