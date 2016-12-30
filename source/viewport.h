// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

struct viewport
{
  viewport(int x_, int y_, int w_, int h_) : x(x_), y(y_), w(w_), h(h_) {}

  int x = 0;
  int y = 0;
  int w = 1;
  int h = 1;
};

inline float aspect_ratio(const viewport& vp)
{
  return static_cast<float>(vp.w) / static_cast<float>(vp.h);
}

