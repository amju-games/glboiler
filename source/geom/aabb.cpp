// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include <algorithm>
#include "gl_includes.h"
#include "aabb.h"

aabb::aabb(const vec3& min, const vec3& max)
{
  // Ensure min < max
  m_min = vec3(std::min(min.x, max.x), std::min(min.y, max.y), std::min(min.z, max.z));
  m_max = vec3(std::max(min.x, max.x), std::max(min.y, max.y), std::max(min.z, max.z));
}

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

void aabb::debug_render_on_gl_thread() const
{
  // Compatibility mode time
  glBegin(GL_LINE_LOOP);
  glVertex3f(m_min.x, m_min.y, m_min.z);
  glVertex3f(m_max.x, m_min.y, m_min.z);
  glVertex3f(m_max.x, m_min.y, m_max.z);
  glVertex3f(m_min.x, m_min.y, m_max.z);
  glEnd();

  glBegin(GL_LINE_LOOP);
  glVertex3f(m_min.x, m_max.y, m_min.z);
  glVertex3f(m_max.x, m_max.y, m_min.z);
  glVertex3f(m_max.x, m_max.y, m_max.z);
  glVertex3f(m_min.x, m_max.y, m_max.z);
  glEnd();

  glBegin(GL_LINES);
  glVertex3f(m_min.x, m_min.y, m_min.z);
  glVertex3f(m_min.x, m_max.y, m_min.z);

  glVertex3f(m_max.x, m_min.y, m_min.z);
  glVertex3f(m_max.x, m_max.y, m_min.z);

  glVertex3f(m_max.x, m_min.y, m_max.z);
  glVertex3f(m_max.x, m_max.y, m_max.z);

  glVertex3f(m_min.x, m_min.y, m_max.z);
  glVertex3f(m_min.x, m_max.y, m_max.z);
  glEnd();
}

aabb* aabb::transform_by(const mat4& m) const
{
  // Transform the 8 corners. Make a new aabb which encloses them.
  vec3 corners[8] = 
  {
    vec3(m_min.x, m_min.y, m_min.z),
    vec3(m_min.x, m_min.y, m_max.z),
    vec3(m_min.x, m_max.y, m_min.z),
    vec3(m_min.x, m_max.y, m_max.z),
    vec3(m_max.x, m_min.y, m_min.z),
    vec3(m_max.x, m_min.y, m_max.z),
    vec3(m_max.x, m_max.y, m_min.z),
    vec3(m_max.x, m_max.y, m_max.z),
  };

  vec3 xformed_corners[8];
  for (int i = 0; i < 8; i++) 
  {
    xformed_corners[i] = mult(m, corners[i]);
  };

  aabb* a(new aabb(xformed_corners[0], xformed_corners[1]));
  for (int i = 2; i < 8; i++)
  {
    a->include(xformed_corners[i]);
  }
  return a;
}

