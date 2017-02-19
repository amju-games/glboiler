// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include "camera.h"

frustum camera::calc_frustum() const
{
  frustum fr;
  mat4 m = mult(proj_matrix, look_at_matrix);
  fr.set_from_matrix(m);
  return fr;
}

