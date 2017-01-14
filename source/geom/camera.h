// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include "frustum.h"
#include "vec3.h"

struct camera 
{
  frustum calc_frustum() const;

  mat4 proj_matrix;
  mat4 look_at_matrix;
};

