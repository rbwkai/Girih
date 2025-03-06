#ifndef ANIM
#define ANIM

#include <bits/stdc++.h>
#include "../canvas/canvas.hpp"
#include "../object/obj.hpp"
#include "../param/parameter.hpp"

#include "constants.hpp"
#include "keyframe.hpp"

template<typename T>
void animate(point& obj,
             canvas& cnv,
             std::vector<keyframe<T>>& keyframes,
             bool last = 1) {

  const int totalSteps = Constant::TOTAL_STEPS;

  for (int step = 0; step <= totalSteps; ++step) {
    float t = (float)(step) / totalSteps;

    for (auto& kf : keyframes) {
      kf.update(t);
    }

    RGBA red(255, 0, 0, 255); // Red with full opacity
    cnv.draw(obj.loc(), red);

    if (!last and step % Constant::STEPS_PER_FRAME == 0) {
      string fn = "render/frame"
                  +to_string(step/Constant::STEPS_PER_FRAME)
                  +".png";
      cnv.render(fn.c_str());
    }
  }
  string ff = "render/render.png";
  cnv.render(ff.c_str());
}

#endif // !ANIM
