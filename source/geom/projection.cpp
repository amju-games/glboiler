// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

#include <math.h>
#include "projection.h"

void perspective::set_matrix(mat4 m) const
{
  double sine, cotangent, deltaZ;
  double radians = fov_y_degs / 2 * M_PI / 180;

  deltaZ = far_distance - near_distance; 
  sine = sin(radians);
  if ((deltaZ == 0) || (sine == 0) || (aspect_ratio == 0)) {
    return;
  }

  cotangent = cos(radians) / sine;

  load_identity(m);
  m[0] = cotangent / aspect_ratio;
  m[5] = cotangent;
  m[10] = -(far_distance + near_distance) / deltaZ;
  m[11] = -1;
  m[14] = -2 * near_distance * far_distance / deltaZ;
  m[15] = 0;
}



