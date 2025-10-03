### Girih
---
***The Geometry Engine***
---
---

## Features (what Girih gives you)
- **Declarative geometric primitives**: `Point`-derived objects (nodes, rotating rotors, intersections, midpoints, etc.), `Line` variants, `Segment`, `Circle`, `ExternalTangent`, and `Text`.
- **Derived parameter values**: `Value` objects that compute things like distances and angles (`Float`, `Proxim`, `PointLineDistance`, `AngleBetweenLines`).
- **Keyframe animation system**: animate numeric fields and colors over a sequence of steps.
- **Canvas + renderer**: draws points, lines, segments, circles, external tangents and text. When producing per-frame output it writes `render/frame%04d.ppm` and always produces a final `render/render.png`.
- **Simple API to compose scenes**: create points/lines/circles, attach keyframes, call `animate(...)`.

---

## Project layout (typical)

/src
/object      # point.hpp, line.hpp, obj.hpp (Nodes, Lines, Segments, Circle, ...)
/anim        # animate.hpp, keyframe.hpp, constants.hpp
/param       # parameter.hpp (Value, Float, Proxim, ...)
/canvas      # canvas.hpp (drawing + render impl)
main.cpp       # example scene(s)
render/        # output frames and final image

````
(Your repository may differ — the README assumes header-first layout shown in examples.)

---

## Build & run (quick start)
1. Build (example; adapt to your project layout):
```bash
mkdir -p build && \
g++ -std=c++17 -O2 -I./src -I. src/*.cpp -o girih
````

2. Run your scene:

```bash
./girih
# Output files:
#  - render/frame0000.ppm .. render/frameNNNN.ppm  (if per-frame rendering enabled)
#  - render/render.png     (final composite image)
```

Notes:

* `canvas` constructors accept a resolution (e.g., `canvas cnv(1024)` or `canvas cnv(1024, 1024)`).
* Adjust the `-I` include paths to match your repo.

---

## Core concepts / API reference (concise)

### Points / Nodes

* `Node(float x=0, float y=0, RGBA color = White)`

  * Basic coordinate point. Has `x, y, color` and `Coord loc() const`.
  * Operators `+`, `-`, `*` are provided for simple composition.

* `Rotor(Point &origin, float len, RGBA color = White)`

  * Represents a point at `origin + (len∠arg)`.
  * `arg` is the rotation angle (radians). `set_rot(float th)` sets angle. Useful for circular motion.

* `PointSum(Point &a, Point &b, function<Coord(const Point&, const Point&)> locFun, RGBA color)`

  * Combines two points using `locFun` (default is vector sum).

### Lines

* `HorizontalLine(Point &ref)` — horizontal line through `ref`.
* `VerticalLine(Point &ref)` — vertical line through `ref`.
* `PerpendicularLine(Line &base, Point &ref)` — line through `ref` perpendicular to `base`.
* `PerpendicularBisector(Point &p1, Point &p2)` — perpendicular bisector of segment `p1p2`.

### Constructed Points

* `IntersectionPoint(Line &l1, Line &l2)` — intersection coordinates.
* `MidPoint(Point &a, Point &b)` — midpoint.
* `Equidistant(Point &a, Point &b)` — point equidistant from `a` and `b` forming a right angle (used where needed in examples).
* `Rotation(Point &center, Point &p)` — rotates `p` by +π/2 about `center`.
* `InternalDivision(Point &a, Point &b, float r)` — point dividing `ab` internally in ratio `1:r`.
* `ExternalDivision(Point &a, Point &b, float r)` — external division (1:r).

### Drawable primitives

* `Segment(Point &start, Point &end, RGBA color = White)`

  * Has `start()` and `end()` helpers for drawing.
* `Circle(Point &center, Value &radius, RGBA color = White)`

  * Radius is a `Value` (so it can be dynamic: distances, floats, etc.)
* `ExternalTangent(Circle &c1, Circle &c2, RGBA color)`

  * Computes the pair of tangent points; `loc()` (or `loc()` equivalent) returns two `Node`s.
* `Text(Point &loc, Value &val, RGBA color = White, int scale = 1)`

  * Draws `val.s + " " + to_string(val.val())` at the given location.

### Parameters (`Value`)

All `Value` types have a `string s` (label) and `virtual float val() const`.

* `Float(float f)` — constant numeric value.
* `Proxim(Point &a, Point &b, string s = "...")` — Euclidean distance between points `a` and `b`.
* `PointLineDistance(Point &p, Line &l, string s = "...")` — distance from a point to a line.
* `AngleBetweenLines(Line &l1, Line &l2, string s = "...")` — smaller angle (radians) between two lines.

These are handy for dynamic circle radii, labels and numeric text.

---

## Keyframes & animation system

* `Keyframe` objects bind to numeric variables (for example `somePoint.x`, `somePoint.y`, `Rotor::arg`, or color variables) and interpolate them from a **start** value to an **end** value across the animation steps.
* The engine uses two important constants:

  * `Constant::TOTAL_STEPS` — total animation steps (granularity of interpolation).
  * `Constant::STEPS_PER_FRAME` — how many steps per output frame (used to write discrete frames).
* `animate(...)` main responsibilities:

  1. For each animation step: call `kf->update(step)` on every keyframe (so bound variables change over time).
  2. Draw `Point` objects (by sampling `Point::loc()`), then draw `Drawable`s (segments, lines, circles, external tangents) and `Text`.
  3. If `last == false` it writes per-frame images as `render/frame%04d.ppm`. At the end always writes `render/render.png`.

**Typical call (as in example scenes):**

```cpp
vector<Point*> objList = { &r1, &I };
vector<Segment*> segList = { &sr, &seg, &seg2 };
vector<Line*> lineList = {};
vector<Circle*> circleList = {};
vector<Keyframe*> keys = { &kf_r1, &kf_tm, &kfc };

animate(objList, segList, lineList, circleList, cnv, keys, /*last=*/0);
```

(Depending on your build you may have slight signature variants — check the header in your repo. The important bits are: pass collections of Points, Segments, Lines, Circles, the `canvas`, keyframes, and the `last` flag.)

---

## Example scenes (copy-pasteable snippets)

Minimal rotating rotor + segments:

```cpp
// inside main.cpp (abridged)
canvas cnv(1024);
Node origin(-200, 0);

// axes
HorizontalLine x_axis(origin);
VerticalLine y_axis(origin);
cnv.draw_line(&x_axis, White, 1);
cnv.draw_line(&y_axis, White, 1);

// rotor around origin
Rotor r1(origin, 120, Maroon);
Keyframe kf_r1(r1.arg, float(0), 2 * pi);

// geometry
Segment sr(origin, r1);
Node anc(200, 0);
Segment sh(r1, anc, Flamingo);
MidPoint M(anc, r1);

// a right-angle rotation about midpoint
Rotation I(M, anc);
Segment s2(I, M, Teal);

// keyframes + animate
vector<Keyframe*> keys = { &kf_r1 };
vector<Point*> objList = { &r1, &I };
vector<Segment*> segList = { &sr, &sh, &s2 };
vector<Line*> lineList = {};
vector<Circle*> circleList = {};

animate(objList, segList, lineList, circleList, cnv, keys, 0);
```

Construct circumcircle example (center = intersection of perpendicular bisectors):

```cpp
canvas cnv(1024, 1024);
Node A(-150, -100), B(150, -100), C(-200, 200);
PerpendicularBisector pb_ab(A,B), pb_ac(A,C);
IntersectionPoint I(pb_ab, pb_ac);
Proxim periR(I, A, "Peri-Radius:");
Circle periC(I, periR, Flamingo);
// segments from center to midpoints
MidPoint Mc(A,B); Segment Sa(I, Mc, Sapphire);
vector<Segment*> segList = { &Sa, /*...*/ };
vector<Circle*> circleList = { &periC };
animate({}, segList, {}, circleList, cnv, {}, 0);
```

---

## Output format & rendering notes

* Per-frame intermediate images: written as **PPM** files `render/frameXXXX.ppm` (useful for ffmpeg conversion).
  Example ffmpeg command to make a video from frames:

  ```bash
  ffmpeg -framerate 24 -i render/frame%04d.ppm -c:v libx264 -pix_fmt yuv420p out.mp4
  ```
* Final composite image: `render/render.png`.
* Canvas resolution is controlled when you construct `canvas cnv(w)` or `canvas cnv(w,h)`.

---

## Tips & extension ideas

* **Make more `Value` types** (e.g., area, line intersection parameter, barycentric combos) to drive radii, labels and keyframes.
* **Add easing** to `Keyframe` so interpolation can be non-linear (ease-in/out).
* **Add more line/curve primitives** (ray, infinite line rendering toggles, arcs).
* **Improve output formats**: add direct PNG-per-frame or animation (APNG) export to skip PPM + ffmpeg step.
* **UI / live preview**: small GUI using SDL or GLFW to preview without writing disk images.

---

## Troubleshooting

* If you see nothing in final PNG: ensure your geometry is inside the canvas coordinate system (check `canvas` coordinate transform and point positions).
* If compile fails with missing headers: check include paths and that all source files from `src/` are passed to `g++`.
* If Keyframe doesn't animate a value: verify you passed a reference (e.g., `r1.arg`) and that Keyframe supports that variable type (float/color).

---

## License

Choose a license for your project (e.g., MIT). Add `LICENSE` file to the repo.

---

## Summary

Girih is a minimal, composable geometry engine focused on converting geometric programs into frame-by-frame animations via:

* Points & derived constructions,
* Value-driven dynamic parameters,
* Keyframed interpolation,
* Simple canvas-based rendering pipeline.

Use the provided point/line/circle primitives + keyframes to express geometric motion quickly. Inspect the headers (`object/obj.hpp`, `param/parameter.hpp`, `anim/animate.hpp`) to see exact function signatures and extend from there.

---

README by ChatGPT:)


