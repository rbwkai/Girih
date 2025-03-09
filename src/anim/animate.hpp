#ifndef ANIM
#define ANIM

#include <bits/stdc++.h>

#include "../canvas/canvas.hpp"
#include "../object/obj.hpp"
#include "../param/parameter.hpp"
#include "constants.hpp"
#include "keyframe.hpp"

void animate(vector<Point*>& pointList, vector<Drawable*> objList, Value& value,
             canvas& cnv, vector<Keyframe*> keyframes, bool last = 1) {
  const int totalSteps = Constant::TOTAL_STEPS;

  for (int step = 0; step <= totalSteps; ++step) {
    // float t = (float) step / totalSteps;
    for (auto& kf : keyframes) {
      kf->update(step);
    }
    for (auto& obj : pointList) {
      cnv.draw(obj->loc(), obj->color);
    }

    if (!last and step % Constant::STEPS_PER_FRAME == 0) {
      ostringstream filename;
      filename << "render/frame" << std::setw(4) << std::setfill('0')
               << step / Constant::STEPS_PER_FRAME << ".png";

      string fn = filename.str();

      for (auto& obj : objList) {
        if (auto seg = dynamic_cast<Segment*>(obj)) {
          cnv.draw(seg, seg->color);
        } else if (auto ln = dynamic_cast<Line*>(obj)) {
          cnv.draw(ln, ln->color, false);
        } else if (auto cir = dynamic_cast<Circle*>(obj)) {
          cnv.draw(cir, cir->color);
        } else if (auto ext = dynamic_cast<ExternalTangent*>(obj)) {
          cnv.draw(ext, ext->color);
        }
      }

      cnv.drawString({-150, 400}, value.s + to_string(value.val()), Flamingo,
                     2);
      cnv.render(fn.c_str());
    }
  }
  string ff = "render/render.png";
  cnv.render(ff.c_str());
}

#endif  // !ANIM
