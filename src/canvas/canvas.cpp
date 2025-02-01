#include "canvas.hpp"
#include "../../lodepng/lodepng.h"

canvas::canvas(int s) : SIZE(s),
                        pix(s, vector<int>(s, 255)),
                        ovl(s, vector<int>(s, 0)){}
void canvas::draw(vec2 p){
  int px = SIZE/2 + p.x;
  int py = SIZE/2 - p.y;

  if (px < 0 || px >= SIZE || py < 0 || py >= SIZE) return;

  for (int dx = -LINE_THICKNESS; dx <= LINE_THICKNESS; ++dx) {
    for (int dy = -LINE_THICKNESS; dy <= LINE_THICKNESS; ++dy) {
      int nx = px + dx;
      int ny = py + dy;

      if (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE) {
        int dist = (dx * dx + dy * dy);
        int del =  255-dist*dist;
        pix[ny][nx] = max(0, pix[ny][nx]-del);
      }
    }
  }
}

void canvas::visl(vec2 p){
  
}

void canvas::render(const char* filename){
  std::vector<unsigned char> image(SIZE*SIZE, 0);
  for(int i=0; i<SIZE; ++i){
    for(int j=0; j<SIZE; ++j){
      int cp = pix[i][j] - ovl[i][j];
      cp=min(cp, 255);
      cp=max(cp, 0);
      image[i*SIZE + j]=cp;
    }
  }

  unsigned err = lodepng::encode(filename,
                             image,
                             SIZE,
                             SIZE,
                             LCT_GREY);

  cout<<(err? "Error": "Saved:")<<filename<<endl;
}

