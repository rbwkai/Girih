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

  rotor r1(200, ori);

  proxim d1(r_start, r1); 

  vector<keyframe<float>> keys = {
    keyframe(r1.arg, (float)0, pi),
  };
  
  cout<<"distance from start: "<<(d1.len())<<endl;
  animate(r1, cnv, keys);
  cout<<"distance from start: "<<(d1.len())<<endl;
}
