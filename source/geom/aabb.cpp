// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include <algorithm>
#include "gl_includes.h"
#include "aabb.h"

cull_result aabb::calc_cull_result(const frustum& fr) const
{
  return cull_result::FRUSTUM_INSIDE;
}

const vec3& aabb::get_min() const
{
  return m_min;
}

const vec3& aabb::get_max() const
{
  return m_max;
}

aabb aabb::union_with(const aabb& other) const
{
  aabb a(*this);
  a.include(other.m_min);
  a.include(other.m_max);
  return a;
}

void aabb::include(const vec3& p)
{
  m_min.x = std::min(m_min.x, p.x);
  m_min.y = std::min(m_min.y, p.y);
  m_min.z = std::min(m_min.z, p.z);
  m_max.x = std::max(m_max.x, p.x);
  m_max.y = std::max(m_max.y, p.y);
  m_max.z = std::max(m_max.z, p.z);
}

void debug_render_on_gl_thread(const aabb& aabb)
{
  // Compatibility mode time
  const vec3& min = aabb.get_min();
  const vec3& max = aabb.get_max();

  glBegin(GL_LINE_LOOP);
  glVertex3f(min.x, min.y, min.z);
  glVertex3f(max.x, min.y, min.z);
  glVertex3f(max.x, min.y, max.z);
  glVertex3f(min.x, min.y, max.z);
  glEnd();

  glBegin(GL_LINE_LOOP);
  glVertex3f(min.x, max.y, min.z);
  glVertex3f(max.x, max.y, min.z);
  glVertex3f(max.x, max.y, max.z);
  glVertex3f(min.x, max.y, max.z);
  glEnd();

  glBegin(GL_LINES);
  glVertex3f(min.x, min.y, min.z);
  glVertex3f(min.x, max.y, min.z);

  glVertex3f(max.x, min.y, min.z);
  glVertex3f(max.x, max.y, min.z);

  glVertex3f(max.x, min.y, max.z);
  glVertex3f(max.x, max.y, max.z);

  glVertex3f(min.x, min.y, max.z);
  glVertex3f(min.x, max.y, max.z);
  glEnd();

}
