// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include "light.h"
#include "look_at.h"
#include "projection.h"

void directional_light::calc_matrix(float size, float near_dist, float far_dist)
{
  ortho o(-size, size, -size, size, near_dist, far_dist);
  mat4 proj;
  o.set_matrix(proj);

  vec3 up(0, 1, 0); // = cross(m_pos, m_dir);
  look_at look(m_pos, m_dir, up);
  mat4 view;
  look.set_matrix(view);

  m_matrix = mult(view, proj);
}


