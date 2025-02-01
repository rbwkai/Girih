#ifndef KEYFRAME
#define KEYFRAME

template<typename T>
struct keyframe {
  T& variable;
  T start, end;

  keyframe(T& var, T sv, T ev) : variable(var),
                                 start(sv), end(ev) {}
  void update(float t){
    variable = start + (end - start)*t;
  }
};

#endif // !KEYFRAME

