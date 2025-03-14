#include "canvas.hpp"

#include <fcntl.h>
#include <unistd.h>

#include <algorithm>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <vector>

#include "../../lodepng/lodepng.h"
#include "../anim/constants.hpp"
#include "font.hpp"

using namespace std;

static RGBA blend(const RGBA &dest, const RGBA &src) {
  RGBA out;
  out.r = (src.r * src.a + dest.r * (255 - src.a)) / 255;
  out.g = (src.g * src.a + dest.g * (255 - src.a)) / 255;
  out.b = (src.b * src.a + dest.b * (255 - src.a)) / 255;
  out.a = src.a + (dest.a * (255 - src.a)) / 255;
  return out;
}

canvas::canvas(int w, int h)
    : WIDTH(w),
      HEIGHT(h),
      pix(h, vector<RGBA>(w, Black)),
      ovrly(h, vector<RGBA>(w, RGBA(0, 0, 0, 0))) {}

void canvas::draw(Coord p, const RGBA &color, bool permanent) {
  float px = WIDTH / 2.0f + p.x;
  float py = HEIGHT / 2.0f - p.y;

  int base_x = floor(px);
  int base_y = floor(py);

  for (int i = base_x - LINE_THICKNESS; i <= base_x + LINE_THICKNESS; ++i) {
    for (int j = base_y - LINE_THICKNESS; j <= base_y + LINE_THICKNESS; ++j) {
      if (i < 0 || i >= WIDTH || j < 0 || j >= HEIGHT) continue;

      float cx = i + 0.5f;
      float cy = j + 0.5f;

      float dx = px - cx;
      float dy = py - cy;
      float dist2 = dx * dx + dy * dy;

      // Option 1: Smoother Gaussian falloff for smoother edges
      float factor = exp(dist2 * inv2_sigma2);
      factor = max(0.0f, min(1.0f, factor));  // Clamp between 0 and 1

      // Option 2: Use smootherstep for more gradual transition
      // float smootherT = sqrt(dist2) / maxDist;
      // factor = smootherT * smootherT * (3 - 2 * smootherT); // Smootherstep

      RGBA modColor = color;
      modColor.a = static_cast<unsigned char>(color.a * factor);

      if (permanent)
        pix[j][i] = blend(pix[j][i], modColor);
      else
        ovrly[j][i] = blend(ovrly[j][i], modColor);
    }
  }
}

void canvas::draw(const Segment *seg, const RGBA &color, bool parmanent) {
  auto [x1, y1] = seg->start()->loc();
  auto [x2, y2] = seg->end()->loc();

  const int steps = hypot(x2 - x1, y2 - y1);  // IMPORTANT

  for (int k = 0; k <= steps; k++) {
    float t = static_cast<float>(k) / steps;
    Coord d = {x2 - x1, y2 - y1};
    Coord p = {x1 + d.x * t, y1 + d.y * t};
    float px = WIDTH / 2.0f + p.x;
    float py = HEIGHT / 2.0f - p.y;
    int base_x = floor(px);
    int base_y = floor(py);
    for (int i = base_x - LINE_THICKNESS; i <= base_x + LINE_THICKNESS; ++i) {
      for (int j = base_y - LINE_THICKNESS; j <= base_y + LINE_THICKNESS; ++j) {
        if (i < 0 || i >= WIDTH || j < 0 || j >= HEIGHT) continue;
        float cx = i + 0.5f;
        float cy = j + 0.5f;
        float dx = px - cx;
        float dy = py - cy;
        float dist2 = dx * dx + dy * dy;

        float factor = exp(dist2 * inv2_sigma2);
        factor = max(0.0f, min(1.0f, factor));
        RGBA modColor = color;
        modColor.a = static_cast<unsigned char>(color.a * factor);
        if (parmanent)
          pix[j][i] = blend(pix[j][i], modColor);
        else
          ovrly[j][i] = blend(ovrly[j][i], modColor);
      }
    }
  }
}
// External Tangent

void canvas::draw(const ExternalTangent *ext, const RGBA &color,
                  bool parmanent) {
  auto [P1, P2] = ext->loc();
  Segment tmp(P1, P2);
  draw(&tmp, color, parmanent);
}

void canvas::draw(const Line *ln, const RGBA &color, bool permanent) {
  // Compute half-sizes of the canvas (assuming canvas coordinates are in
  // [-half, half] for each axis)
  float halfX = WIDTH / 2.0f;
  float halfY = HEIGHT / 2.0f;
  l_eqn eq = ln->eqn();
  float a = eq.a, b = eq.b, c = eq.c;
  const float eps = 1e-6f;
  std::vector<Coord> intersections;

  // Intersect with vertical boundaries: x = -halfX and x = halfX
  if (fabs(b) > eps) {
    {
      float x = -halfX;
      float y = -(c + a * x) / b;
      if (y >= -halfY && y <= halfY) intersections.push_back({x, y});
    }
    {
      float x = halfX;
      float y = -(c + a * x) / b;
      if (y >= -halfY && y <= halfY) intersections.push_back({x, y});
    }
  }

  // Intersect with horizontal boundaries: y = -halfY and y = halfY
  if (fabs(a) > eps) {
    {
      float y = -halfY;
      float x = -(c + b * y) / a;
      if (x >= -halfX && x <= halfX) intersections.push_back({x, y});
    }
    {
      float y = halfY;
      float x = -(c + b * y) / a;
      if (x >= -halfX && x <= halfX) intersections.push_back({x, y});
    }
  }

  // If there are fewer than 2 intersections, the line does not cross the frame.
  if (intersections.size() < 2) return;

  // Remove any duplicate intersection points (if any)
  auto unique_end =
      std::unique(intersections.begin(), intersections.end(),
                  [eps](const Coord &p1, const Coord &p2) {
                    return fabs(p1.x - p2.x) < eps && fabs(p1.y - p2.y) < eps;
                  });
  intersections.erase(unique_end, intersections.end());

  // In case more than two intersections were found, pick the two that are
  // farthest apart.
  if (intersections.size() > 2) {
    float maxDist = -1.0f;
    Coord pt1, pt2;
    for (size_t i = 0; i < intersections.size(); ++i) {
      for (size_t j = i + 1; j < intersections.size(); ++j) {
        float dx = intersections[i].x - intersections[j].x;
        float dy = intersections[i].y - intersections[j].y;
        float d = sqrt(dx * dx + dy * dy);
        if (d > maxDist) {
          maxDist = d;
          pt1 = intersections[i];
          pt2 = intersections[j];
        }
      }
    }
    intersections.clear();
    intersections.push_back(pt1);
    intersections.push_back(pt2);
  }

  // Now we have exactly two endpoints from the intersection:
  Coord start = intersections[0];
  Coord end = intersections[1];

  const int steps = 1000;  // IMPORTANT
  const float maxDist = LINE_THICKNESS + MAXDIS_PARAM;
  const float sigma = maxDist / SIGMA_PARAM;
  const float inv2_sigma2 = -1.0f / (2.0f * sigma * sigma);

  for (int k = 0; k <= steps; k++) {
    float t = static_cast<float>(k) / steps;
    Coord d = {end.x - start.x, end.y - start.y};
    Coord p = {start.x + d.x * t, start.y + d.y * t};

    // Transform mathematical coordinates to pixel coordinates.
    float px = WIDTH / 2.0f + p.x;
    float py = HEIGHT / 2.0f - p.y;
    int base_x = floor(px);
    int base_y = floor(py);

    for (int i = base_x - LINE_THICKNESS; i <= base_x + LINE_THICKNESS; ++i) {
      for (int j = base_y - LINE_THICKNESS; j <= base_y + LINE_THICKNESS; ++j) {
        if (i < 0 || i >= WIDTH || j < 0 || j >= HEIGHT) continue;

        float cx = i + 0.5f;
        float cy = j + 0.5f;
        float dx = px - cx;
        float dy = py - cy;
        float dist2 = dx * dx + dy * dy;

        float factor = exp(dist2 * inv2_sigma2);
        factor = max(0.0f, min(1.0f, factor));  // Clamp between 0 and 1

        RGBA modColor = color;
        modColor.a = static_cast<unsigned char>(color.a * factor);

        if (permanent)
          pix[j][i] = blend(pix[j][i], modColor);
        else
          ovrly[j][i] = blend(ovrly[j][i], modColor);
      }
    }
  }
}

void canvas::draw(const Circle *cir, const RGBA &color, bool parmanent) {
  Coord center = cir->center.loc();
  float radius = cir->radius.val();
  const int steps =
      4.0 * M_PI * radius;  // Number of points sampled on the circle
  const float step_angle = 2.0f * M_PI / steps;  // Precompute step size

  float px_center = WIDTH / 2.0f + center.x;
  float py_center = HEIGHT / 2.0f - center.y;

  for (int k = 0; k <= steps; k++) {
    float px = px_center + radius * cos(k * step_angle);
    float py =
        py_center -
        radius * sin(k * step_angle);  // Y is inverted for screen coordinates

    int base_x = (int)px;
    int base_y = (int)py;

    for (int i = base_x - LINE_THICKNESS; i <= base_x + LINE_THICKNESS; ++i) {
      for (int j = base_y - LINE_THICKNESS; j <= base_y + LINE_THICKNESS; ++j) {
        if (i < 0 || i >= WIDTH || j < 0 || j >= HEIGHT) continue;

        float dx = px - (i + 0.5f);
        float dy = py - (j + 0.5f);
        float dist2 = dx * dx + dy * dy;

        float factor = exp(dist2 * inv2_sigma2);  // Faster Gaussian computation
        factor = max(0.0f, min(1.0f, factor));

        RGBA modColor = color;
        modColor.a = static_cast<unsigned char>(color.a * factor);

        if (parmanent)
          pix[j][i] = blend(pix[j][i], modColor);
        else
          ovrly[j][i] = blend(ovrly[j][i], modColor);
      }
    }
  }
}

void canvas::drawChar(Coord p, char c, const RGBA &color, int scale,
                      int permanent) {
  if (c < 32 || c > 122) return;  // Supported range
  vector<uint16_t> glyph;
  if (c >= '0' and c <= '9') {
    glyph = FONT_8x12_DIGIT[c - '0'];
  } else if (c >= 'a' and c <= 'z') {
    glyph = FONT_8x12_LOWER[c - 'a'];
  } else if (c >= 'A' and c <= 'Z') {
    glyph = FONT_8x12_UPPER[c - 'A'];
  } else {
    if (FONT_8x12_SPECIAL.count(c) == 0) return;
    glyph = FONT_8x12_SPECIAL[c];
  }
  auto [x, y] = p;
  for (int row = 0; row < 12; ++row) {
    for (int col = 0; col < 8; ++col) {
      if (glyph[row] & (1 << (7 - col))) {
        for (int dx = 0; dx < scale; ++dx) {
          for (int dy = 0; dy < scale; ++dy) {
            draw({x + col * scale + dx, y - row * scale + dy}, color,
                 permanent);
          }
        }
      }
    }
  }
}

void canvas::drawString(Coord p, const string text, const RGBA &color,
                        int scale, int permanent) {
  int spacing = 8 * scale + 5;
  for (size_t i = 0; i < text.size(); ++i) {
    drawChar({p.x + i * spacing, p.y}, text[i], color, scale, permanent);
  }
}

////////////////////////////////////////////////////////////////////////

void canvas::render(const char *filename) {
  std::ofstream file(filename, std::ios::binary);
  if (!file) {
    std::cerr << "Error opening file: " << filename << std::endl;
    return;
  }

  // Write PPM header
  file << "P6\n" << WIDTH << " " << HEIGHT << "\n255\n";

  // Buffer all pixel data
  vector<unsigned char> buffer(WIDTH * HEIGHT * 3);
  unsigned idx = 0;

  for (int i = 0; i < HEIGHT; ++i) {
    for (int j = 0; j < WIDTH; ++j) {
      RGBA combined = blend(pix[i][j], ovrly[i][j]);
      buffer[idx++] = combined.r;
      buffer[idx++] = combined.g;
      buffer[idx++] = combined.b;
    }
  }

  // Single write call for all pixel data
  file.write(reinterpret_cast<char *>(buffer.data()), buffer.size());
  file.close();

  std::cout << "Saved: " << filename << std::endl;

  // **Optimized overlay clearing**
  static const std::vector<RGBA> zeroRow(WIDTH, RGBA(0, 0, 0, 0));
  for (auto &row : ovrly) {
    row = zeroRow;  // Efficient row assignment
  }
}

// --------   Use this for png image   ------- //

// void canvas::render(const char *filename) {
//   std::vector<unsigned char> image(WIDTH * HEIGHT * 4, 0);

//   for (int i = 0; i < HEIGHT; ++i) {
//     for (int j = 0; j < WIDTH; ++j) {
//       RGBA combined = blend(pix[i][j], ovrly[i][j]);

//       int idx = (i * WIDTH + j) * 4;
//       image[idx + 0] = combined.r;
//       image[idx + 1] = combined.g;
//       image[idx + 2] = combined.b;
//       image[idx + 3] = combined.a;
//     }
//   }
//   unsigned err = lodepng::encode(filename, image, WIDTH, HEIGHT, LCT_RGBA);
//   cout << (err ? "Error: " : "Saved: ") << filename << endl;

//   ovrly.assign(HEIGHT, std::vector<RGBA>(WIDTH, RGBA(0, 0, 0, 0)));
// }
