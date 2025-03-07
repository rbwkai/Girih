#ifndef ANIM
#define ANIM

#include <bits/stdc++.h>

#include "../canvas/canvas.hpp"
#include "../object/obj.hpp"
#include "../param/parameter.hpp"
#include "constants.hpp"
#include "keyframe.hpp"

void animate(vector<point*>& objList, vector<segment*> &segList, vector<line*>& lineList, canvas& cnv, RGBA& color,
             std::vector<Keyframe> keyframes, bool last = 1) {
  const int totalSteps = Constant::TOTAL_STEPS;

  for (int step = 0; step <= totalSteps; ++step) {
    float t = (float)(step) / totalSteps;

    for (auto& kf : keyframes) {
      kf.update(t);
    }
    for(auto& obj: objList){
      cnv.draw(obj->loc(), color);
    }
    
    if (!last and step % Constant::STEPS_PER_FRAME == 0) {
      string fn =
          "render/frame" + to_string(step / Constant::STEPS_PER_FRAME) + ".png";

      for(const auto& ln: lineList){
        cnv.draw_line(ln, color);
      }
      for(auto seg: segList){
        cnv.draw_segment(seg, color);
      }
      cnv.render(fn.c_str());
    }
  }
  string ff = "render/render.png";
  cnv.render(ff.c_str());
}

#endif  // !ANIM
