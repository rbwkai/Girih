#include <bits/stdc++.h> 

#include "./anim/animate.hpp"

using namespace std;

float pi = std::numbers::pi;
int main(){
  node ori;
  rotor r1(200, ori);
  rotor r2(130, r1);

  canvas cnv;

  vector<keyframe<float>> keys = {
    keyframe(r1.arg, (float)0, (float)2*pi),
    keyframe(r2.arg, (float)0, (float)6*pi)
  };
  
  animate(r2, cnv, keys, 0);
}
