#ifndef POINT
#define POINT

struct vec2 {
  float x, y;
  vec2(float x = 0, float y = 0);

  vec2 operator+(const vec2& other) const;
};

struct point {
  virtual ~point() = default;
  virtual vec2 loc() const = 0;
};

struct node : public point{
  vec2 v;

  node(float x = 0, float y = 0);
  vec2 loc() const override;
};

struct rotor : public point{
  float len, arg;
  point& origin;

  rotor(float l, point& p);
  vec2 loc() const override;

  void set_rot(float th);
};

#endif // !POINT
