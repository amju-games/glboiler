// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include "aabb.h"
#include "gl_includes.h"
#include "gl_2_solid_scene_node.h"

gl_2_plane_scene_node::gl_2_plane_scene_node()
{
  m_bounding_vol.reset(new aabb);
}

void gl_2_plane_scene_node::render() const
{
  glBegin(GL_QUADS);
  float x = 5.0f;
  float y = 0.0f;
  float z = 5.0f;
  glNormal3f(0, 1, 0);
  glVertex3f(x, y, z);
  glVertex3f(-x, y, z);
  glVertex3f(-x, y, -z);
  glVertex3f(x, y, -z);
  glEnd();
}

// -----------------------------------------------------------------------------

gl_2_sphere_scene_node::gl_2_sphere_scene_node()
{
  m_bounding_vol.reset(new aabb);
}

void gl_2_sphere_scene_node::render() const
{
  glutSolidSphere(1, 100, 100);
}

// -----------------------------------------------------------------------------

gl_2_teapot_scene_node::gl_2_teapot_scene_node()
{
  m_bounding_vol.reset(new aabb);
}

void gl_2_teapot_scene_node::render() const
{
  glutSolidTeapot(1);
}

