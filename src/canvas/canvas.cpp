#include "canvas.hpp"
#include "../../lodepng/lodepng.h"
#include <algorithm>
#include <iostream>

using namespace std;

// Helper blending function using "source over" alpha blending.
static RGBA blend(const RGBA &dest, const RGBA &src) {
    RGBA out;
    out.r = (src.r * src.a + dest.r * (255 - src.a)) / 255;
    out.g = (src.g * src.a + dest.g * (255 - src.a)) / 255;
    out.b = (src.b * src.a + dest.b * (255 - src.a)) / 255;
    out.a = src.a + (dest.a * (255 - src.a)) / 255;
    return out;
}

canvas::canvas(int s) : SIZE(s),
                        pix(s, vector<RGBA>(s, RGBA())) {} // default: opaque white

void canvas::draw(vec2 p, const RGBA &color) {
    int px = SIZE/2 + p.x;
    int py = SIZE/2 - p.y;

    if (px < 0 || px >= SIZE || py < 0 || py >= SIZE) return;

    for (int dx = -LINE_THICKNESS; dx <= LINE_THICKNESS; ++dx) {
        for (int dy = -LINE_THICKNESS; dy <= LINE_THICKNESS; ++dy) {
            int nx = px + dx;
            int ny = py + dy;

            if (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE) {
                int dist = dx * dx + dy * dy;
                int factor = 255 - dist * dist;
                if (factor < 0) factor = 0;

                RGBA modColor = color;
                modColor.a = (color.a * factor) / 255;

                pix[ny][nx] = blend(pix[ny][nx], modColor);
            }
        }
    }
}

void canvas::visl(vec2 p){
}

void canvas::render(const char* filename){
    std::vector<unsigned char> image(SIZE * SIZE * 4, 0);
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            int idx = (i * SIZE + j) * 4;
            image[idx + 0] = pix[i][j].r;
            image[idx + 1] = pix[i][j].g;
            image[idx + 2] = pix[i][j].b;
            image[idx + 3] = pix[i][j].a;
        }
    }

    unsigned err = lodepng::encode(filename,
                                   image,
                                   SIZE,
                                   SIZE,
                                   LCT_RGBA);

    cout << (err ? "Error" : "Saved:") << filename << endl;
}
