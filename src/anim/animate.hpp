#ifndef ANIM
#define ANIM

#include <bits/stdc++.h>

#include "../canvas/canvas.hpp"
#include "../object/obj.hpp"
#include "../param/parameter.hpp"
#include "constants.hpp"
#include "keyframe.hpp"

void animate(vector<Point*>& objList, vector<segment*> &segList, vector<Line*>& lineList, vector<Circle*> circleList, canvas& cnv, vector<Keyframe*> keyframes, bool last = 1) {
  const int totalSteps = Constant::TOTAL_STEPS;

  for (int step = 0; step <= totalSteps; ++step) {
    float t = (float)(step) / totalSteps;

    for (auto& kf : keyframes) {
      kf->update(t);
    }
    for(auto& obj: objList){
      cnv.draw(obj->loc(), obj->color);
    }
    
    if (!last and step % Constant::STEPS_PER_FRAME == 0) {
      ostringstream filename;
      filename << "render/frame" << std::setw(4) << std::setfill('0') << step / Constant::STEPS_PER_FRAME << ".png";
      
      string fn = filename.str();

      for(const auto& ln: lineList){
        cnv.draw_line(ln, ln->color);
      }
      for(auto seg: segList){
        cnv.draw_segment(seg, seg->color);
      }
      for(auto cir: circleList){
        cnv.draw_circle(cir, cir->color);
      }
      cnv.render(fn.c_str());
    }
  }
  string ff = "render/render.png";
  cnv.render(ff.c_str());
}

#endif  // !ANIM
