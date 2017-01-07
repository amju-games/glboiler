// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

#include "look_at.h"

void look_at::set_matrix(mat4& m) const
{
  // up and dir are normalised in ctor
  vec3 right = normalise(cross(dir, up)); // so this normalise unnecessary?
  vec3 u = normalise(cross(right, dir)); // new orthogonal up vec

  mat4 r; // rotation matrix
  r[0] = right.x;
  r[4] = right.y;
  r[8] = right.z;

  r[1] = u.x;
  r[5] = u.y;
  r[9] = u.z;

  r[2]  = -dir.x;
  r[6]  = -dir.y;
  r[10] = -dir.z;

  mat4 t; 
  t.translate(-eye);

  m = mult(t, r);
}

