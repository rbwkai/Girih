
#include <bits/stdc++.h>
#include "parameter.hpp"

//proxim
Proxim::Proxim(Point& a, Point&b, string s) : a(a), b(b), Value(s) {}
float Proxim::val() const {
  Coord al = a.loc();
  Coord bl = b.loc();

  float dx = al.x - bl.x;
  float dy = al.y - bl.y;
  return sqrt(dx*dx + dy*dy);
}

Float::Float(float dis) : dis(dis), Value("") {}
float Float::val() const{
    return dis;
}

PointLineDistance::PointLineDistance(Point& p, Line& l, string s) : point(p), line(l), Value(s) {}

float PointLineDistance::val() const {
    l_eqn eq = line.eqn();
    float a = eq.a, b = eq.b, c = eq.c;

    float px = point.loc().x;
    float py = point.loc().y;

    // Distance formula: |ax + by + c| / sqrt(a² + b²)
    return std::abs(a * px + b * py + c) / std::sqrt(a * a + b * b);
}


AngleBetweenLines::AngleBetweenLines(Line& line1, Line& line2, string s) : l1(line1), l2(line2), Value(s) {}

float AngleBetweenLines::val() const {
    l_eqn eq1 = l1.eqn();
    l_eqn eq2 = l2.eqn();

    float a1 = eq1.a, b1 = eq1.b;
    float a2 = eq2.a, b2 = eq2.b;

    float m1 = (b1 != 0) ? -a1 / b1 : INFINITY;
    float m2 = (b2 != 0) ? -a2 / b2 : INFINITY;


    if (m1 == INFINITY && m2 == INFINITY) return 0.0f;

    // If one line is vertical, the angle is always 90 degrees
    if (m1 == INFINITY) return M_PI / 2;
    if (m2 == INFINITY) return M_PI / 2;

    // Compute the absolute angle using the formula:
    // θ = |atan(m1) - atan(m2)|
    float theta = std::abs(std::atan(m1) - std::atan(m2));

    // Ensure the smallest angle (θ should be in [0, π/2])
    if (theta > M_PI / 2) {
        theta = M_PI - theta;
    }

    return theta;
}