#ifndef CONSTANT
#define CONSTANT

namespace Constant {
  constexpr int FRAME_RATE = 30;
  constexpr float DURATION = 2.0;
  constexpr int STEPS_PER_FRAME = 100; //point density: more the better
  constexpr int TOTAL_STEPS = FRAME_RATE * DURATION * STEPS_PER_FRAME;
}

#endif // !CONSTANT
