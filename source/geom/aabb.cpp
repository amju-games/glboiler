// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

#include "aabb.h"

cull_result aabb::calc_cull_result(const frustum& fr) const
{
  return cull_result::FRUSTUM_INSIDE;
}

vec3 aabb::get_min() const
{
  return m_min;
}

vec3 aabb::get_max() const
{
  return m_max;
}


