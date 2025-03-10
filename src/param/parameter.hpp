#ifndef PARAM
#define PARAM

#include <string>
#include "../object/core/point.hpp"
#include "../object/core/line.hpp"

struct Value{
  string s;
  Value(string s) : s(s) {}
  virtual ~Value() = default;
  virtual float val() const = 0;
};

struct Float : public Value{
  float dis;
  Float(float dis);
  float val() const;
};

struct Proxim : public Value{
  Point& a;
  Point& b;
  float dis;
  Proxim(Point& a, Point& b, string s = "Distance of Points: ");
  float val() const override;
};

// Struct to calculate distance of a Point from a Line (for param)
struct PointLineDistance : public Value {
    Point& point;
    Line& line;

    PointLineDistance(Point& p, Line& l, string s = "Distance to Line: ");
    float val() const;
};

// returns smaller angle between two lines  (for param)
struct AngleBetweenLines : public Value {
    Line& l1;
    Line& l2;

    AngleBetweenLines(Line& line1, Line& line2, string s = "Angle between: ");
    float val() const; // Returns angle in radians
};

#endif // !PARAM
