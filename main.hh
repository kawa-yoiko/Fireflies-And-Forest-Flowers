#ifndef _main_hh_
#define _main_hh_

static const int W = 800;
static const int H = 450;

class scene {
public:
  virtual void update() {};
  virtual void draw() {};
  virtual void pton(float, float) {};
  virtual void ptmove(float, float) {};
  virtual void ptoff(float, float) {};
};

scene *scene_startup();

#endif