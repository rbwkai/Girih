#include <bits/stdc++.h> 

#include "object/point.hpp"
#include "canvas/canvas.hpp"
using namespace std;

double pi = std::numbers::pi;
int main(){
  node ori;
  rotor r1(200, ori);
  rotor r2(130, r1);

  canvas cnv;

  int Frame = 60;
  int Duration = 2;

  int totFrame = Frame*Duration;
  int totStep = totFrame * 500;

  double inc = (double)2*pi/totStep;
  for(int i=0; i <totFrame; i++){
    for(int j=0; j<500; j++){
      cnv.draw(r2.loc());
      r1.set_rot((i*500+j)*inc);
      r2.set_rot((i*500+j)*inc * 2);
    }
    string filename = "render/frame"+to_string(i)+".png";
    cnv.render(filename.c_str());
  }

  r1.set_rot(atan(0.75));
}
