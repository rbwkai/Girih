#include <bits/stdc++.h> 

#include "./object/obj.hpp"
#include "./param/parameter.hpp"
#include "./anim/animate.hpp"

using namespace std;

float pi = std::numbers::pi;
int main(){
  canvas cnv;

  node ori;
  node r_start(200, 0);

  rotor r1(256, ori); Keyframe kf1(r1.arg, (float)0, 4*pi);

  rotor r2(128, r1); Keyframe kf2(r2.arg, (float)0, 2*pi);

  rotor r3(64, r2); Keyframe kf3(r3.arg, (float)0, -8*pi);

  proxim d1(r_start, r1); 

  RGBA red(255, 0, 0, 255);
  RGBA blue(0, 0, 255, 255);
  RGBA pen; Keyframe kfc(pen, red, blue);

  vector<Keyframe> keys = {
    kf1, kf2, kf3, kfc
  };
  
  cout<<"distance from start: "<<(d1.len())<<endl;
  animate(r3, cnv, pen, keys, 0);
  cout<<"distance from start: "<<(d1.len())<<endl;
}
