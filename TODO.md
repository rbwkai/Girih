# demo main PSEUDOcode for sine wave animation
```
canvas cnv;

node ori; //(0, 0)
rotor r(50, ori); //radius spinning at ori;
node t(100, 0); //point that represents time in x axis;

Horizontal_line H(r); //Horizontal_line though r endpoint;
Vertical_line V(t); //kindoff a timeline

Intersection I(H, V);

keyframes {  //final code not fixed yet
  t from (100, 0) to (200, 0),
  rotor argument from (0 rad) to (2*pi rad)
}

animate(I, cnv, color, keyframes, 0);
```

## Task Distribution
Regardless the specifics, we all should
- Brainstorm
- Share Ideas and Progress to each other
- Ask for suggetions when stuck.

### Nayeem
- Define Line virtual struct @ src/object/core/line.hpp
- Implement a "line drawing" function
- Help Kabir in the "keyframe animation part" 
- Text Rendering if you're REALLYYY motivated.
> kabir is kinda stuck; 
> \-kabir

### Satty
- Implement RGBA color 
- Implement the draw function @ canvas/canvas.cpp
    - the curve drawn from many points should be *smooth*
    - Colors should be consistent(edgecase: a single pixel might get colored multiple times)


### Hasan
- Think of, and formulate as much useful **constraints** as possible.
- After nayeem defines Line, implement those constraints.
    - ***some useful constraints are***:
    - Midpoint
    - Internal and External Division points
    - Reflections
    - pi/2 rotation points
    - Equidistant point

### Kabir
- Work of Keyframing
- Visualization class (suspence for now, WIP)

---
lets cook.
