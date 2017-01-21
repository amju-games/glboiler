// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include "aabb.h"
#include "gl_includes.h"
#include "solid_scene_node.h"

plane_scene_node::plane_scene_node()
{
  m_bounding_vol.reset(new aabb);
}

void plane_scene_node::render() const
{
  glBegin(GL_QUADS);
  float x = 100.0f;
  float y = 0.0f;
  float z = 100.0f;
  glNormal3f(0, 1, 0);
  glVertex3f(x, y, z);
  glVertex3f(x, y, -z);
  glVertex3f(-x, y, -z);
  glVertex3f(-x, y, z);
  glEnd();
}

// -----------------------------------------------------------------------------

sphere_scene_node::sphere_scene_node()
{
  m_bounding_vol.reset(new aabb);
}

void sphere_scene_node::render() const
{
  glutSolidSphere(1, 100, 100);
}

// -----------------------------------------------------------------------------

teapot_scene_node::teapot_scene_node()
{
  m_bounding_vol.reset(new aabb);
}

void teapot_scene_node::render() const
{
  glutSolidTeapot(1);
}

