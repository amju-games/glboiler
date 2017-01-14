// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include "aabb.h"
#include "gl_includes.h"
#include "teapot_scene_node.h"

teapot_scene_node::teapot_scene_node()
{
  m_bounding_vol.reset(new aabb);
}

void teapot_scene_node::render() const
{
  glutSolidSphere(1, 100, 100);
//    glutSolidTeapot(1);

  glBegin(GL_QUADS);
  float x = 5.0f;
  float y = -2.0f;
  float z = 5.0f;
  glVertex3f(x, y, z);
  glVertex3f(x, y, -z);
  glVertex3f(-x, y, -z);
  glVertex3f(-x, y, z);
  glEnd();
}

