#ifndef CONSTANT
#define CONSTANT

namespace Constant {
constexpr int FRAME_RATE = 30;
constexpr float DURATION = 3.0;
constexpr int STEPS_PER_FRAME = 1200;  // point density: more the better
constexpr int TOTAL_STEPS = FRAME_RATE * DURATION * STEPS_PER_FRAME;
}  // namespace Constant

#endif  // !CONSTANT
