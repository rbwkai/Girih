#ifndef CONSTANT
#define CONSTANT

const float pi = 3.1415927410125732421875;

namespace Constant {
constexpr int FRAME_RATE = 60;
constexpr float DURATION = 10.0;
constexpr int STEPS_PER_FRAME = 1200;  // point density: more the better // reduce this if no point is being traced
constexpr int TOTAL_STEPS = FRAME_RATE * DURATION * STEPS_PER_FRAME;
}  // namespace Constant

#endif  // !CONSTANT
