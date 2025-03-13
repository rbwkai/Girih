#ifndef ANIM
#define ANIM

#include <bits/stdc++.h>

#include "../canvas/canvas.hpp"
#include "../object/obj.hpp"
#include "../param/parameter.hpp"
#include "constants.hpp"
#include "keyframe.hpp"

void animate(vector<tuple<Point*, int>>& pointList, vector<tuple<Drawable*, int>> objList, vector<tuple<Text*, int>> textList, canvas& cnv, vector<Keyframe*> keyframes, bool last = 1) {
  const int totalSteps = Constant::TOTAL_STEPS;

  for (int step = 0; step <= totalSteps; ++step) {
    for (auto& kf : keyframes) {
      kf->update(step);
    }
    for (auto& [obj, parmament] : pointList) {
      cnv.draw(obj->loc(), obj->color, parmament);
    }

    if (!last and step % Constant::STEPS_PER_FRAME == 0) {
      ostringstream filename;
      filename << "render/frame" << std::setw(4) << std::setfill('0')
               << step / Constant::STEPS_PER_FRAME << ".png";

      string fn = filename.str();

      for (auto& [obj, parmanent] : objList) {
        if (auto seg = dynamic_cast<Segment*>(obj)) {
          cnv.draw(seg, seg->color, parmanent);
        } else if (auto ln = dynamic_cast<Line*>(obj)) {
          cnv.draw(ln, ln->color, parmanent);
        } else if (auto cir = dynamic_cast<Circle*>(obj)) {
          cnv.draw(cir, cir->color, parmanent);
        } else if (auto ext = dynamic_cast<ExternalTangent*>(obj)) {
          cnv.draw(ext, ext->color, parmanent);
        } 
      }
      for(auto& [txt, parmanent]: textList){
        cnv.drawString(txt->loc.loc() ,txt->val.s + " " + to_string(txt->val.val()), txt->color, txt->scale, 0);
      }
      
      cnv.render(fn.c_str());
    }
  }
  string ff = "render/render.png";
  cnv.render(ff.c_str());
}

#endif  // !ANIM
