#include <bits/stdc++.h> 

#include "./object/obj.hpp"
#include "./param/parameter.hpp"
#include "./anim/animate.hpp"

using namespace std;

float pi = 3.141592654;
int main(){
  canvas cnv;

  node ori;
  node r_start(200, 0);

  rotor r1(256, ori);
  rotor r2(128, r1);
  rotor r3(64, r2);

  proxim d1(r_start, r1); 

  vector<keyframe<float>> keys = {
    keyframe<float>(r1.arg, (float)0, 4*pi),
    keyframe<float>(r2.arg, (float)0, 2*pi),
    keyframe<float>(r3.arg, (float)0, -8*pi),
  };
  
  cout<<"distance from start: "<<(d1.len())<<endl;
  animate(r3, cnv, keys, 0);
  cout<<"distance from start: "<<(d1.len())<<endl;
}
