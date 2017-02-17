// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include "vec3.h"

struct plane
{
  plane() : n(vec3(0, 1, 0)), d(0) {}
  plane(float a_, float b_, float c_, float d_) : n(vec3(a_, b_, c_)), d(d_) {}
  plane(const vec3& n_, float d_) : n(n_), d(d_) {}

  plane& normalise()
  {
    float f = 1.f / length(n);
    n = n * f;
    d *= f;

    return *this;
  }

  vec3 n; // normal
  float d; // distance
};
