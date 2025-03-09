#include <bits/stdc++.h>

#include "./anim/animate.hpp"
#include "./object/obj.hpp"
#include "./param/parameter.hpp"

using namespace std;

float pi = 3.1415927410125732421875;

int main() {
  canvas cnv(1024, 1024);

  Node A(-150, -100);
  Node B(150, -100);

  Node C(-200, 200); 
  Keyframe kcx(C.x, float(-200), float(200));
  Keyframe kcy(C.y, float(200), float(100));
;

  Segment ab(A, B, Sapphire), bc(B, C, Maroon), ca(C, A, Teal);

  PerpendicularBisector pc(A, B), pb(A, C);
  IntersectionPoint I(pc, pb);
  
  Proxim periR(I, A, "Peri-Radius: ");
  Circle periC(I, periR, Flamingo);

  Node nodea(-300, 90);
  Rotor nodec(70, nodea);
  Keyframe kfa(nodec.arg, float(0), 2 * pi);
  Float radius(50);
  Circle c1(nodec, radius);
  ExternalTangent ext(periC, c1);

  MidPoint Mc(A, B), Ma(B, C), Mb(A, C);
  Segment Sa(I, Mc, Sapphire), Sb(I, Ma, Maroon), Sc(I, Mb, Teal);

vector<Drawable*> objList{
  &ab, &bc, &ca, &Sa, &Sb, &Sc, &periC, &c1, &ext
};
vector<Point*> pointList = {};
vector<Keyframe*> keys = {&kcx, &kcy, &kfa};


animate(pointList, objList, periR, cnv, keys, 0);

}
