// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include "mat4.h"
#include "vec3.h"

struct look_at
{
  look_at(const vec3& eye_, const vec3& dir_, const vec3& up_) :
    eye(eye_), dir(normalise(dir_)), up(normalise(up_)) {}

  void set_matrix(mat4) const;

  vec3 eye;
  vec3 dir;
  vec3 up;
};


