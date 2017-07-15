// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include <algorithm>
#include "bounding_sphere.h"
#include "gl_includes.h"

cull_result bounding_sphere::calc_cull_result(const frustum& fr) const
{
  return cull_result::FRUSTUM_INSIDE;
}

bounding_sphere* bounding_sphere::transform_by(const mat4& m) const
{
  // Transform centre (and radius?) by matrix m

  // Get largest scale factor and use this to transform radius?
  float radius_mult = std::max(m[0], std::max(m[5], m[10]));

  bounding_sphere* a(new bounding_sphere(mult(m, m_centre), m_radius * radius_mult));
  return a;
}

void bounding_sphere::debug_render_on_gl_thread() const
{
//  GL_CHECK(glPushMatrix());
  GL_CHECK(glTranslatef(m_centre.x, m_centre.y, m_centre.z));
  glutWireSphere(m_radius, 10, 10);

//  GL_CHECK(glPopMatrix());
}

