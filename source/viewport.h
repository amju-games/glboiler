// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

struct viewport
{
  viewport() = default;
  viewport(int x_, int y_, int w_, int h_) : x(x_), y(y_), w(w_), h(h_) {}

  void set_gl_viewport() const;

  int x = 0;
  int y = 0;
  int w = 1;
  int h = 1;
};

inline float aspect_ratio(const viewport& vp)
{
  return static_cast<float>(vp.w) / static_cast<float>(vp.h);
}

