// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include "aabb.h"
#include "gl_includes.h"
#include "gl_1_1_solid_scene_node.h"

gl_1_1_plane_scene_node::gl_1_1_plane_scene_node()
{
  m_bounding_vol.reset(new aabb);
}

void gl_1_1_plane_scene_node::render_on_gl_thread() const
{
  glBegin(GL_QUADS);
  float x = 5.0f;
  float y = 0.0f;
  float z = 5.0f;
  glNormal3f(0, 1, 0);
  glTexCoord2f(1, 1);
  glVertex3f(x, y, z);
  glTexCoord2f(0, 1);
  glVertex3f(-x, y, z);
  glTexCoord2f(0, 0);
  glVertex3f(-x, y, -z);
  glTexCoord2f(1, 0);
  glVertex3f(x, y, -z);
  glEnd();
}

// -----------------------------------------------------------------------------

gl_1_1_sphere_scene_node::gl_1_1_sphere_scene_node()
{
  m_bounding_vol.reset(new aabb);
}

void gl_1_1_sphere_scene_node::render_on_gl_thread() const
{
  glutSolidSphere(1, 100, 100);
}

// -----------------------------------------------------------------------------

gl_1_1_teapot_scene_node::gl_1_1_teapot_scene_node()
{
  m_bounding_vol.reset(new aabb);
}

void gl_1_1_teapot_scene_node::render_on_gl_thread() const
{
  // Undo the transforms in glutSolidTeapot() - because they use gl 1.1 functions
  //  and won't be applied to gl 2+. This way we get consistent teapots.
  GL_CHECK(glPushMatrix());
  GL_CHECK(glTranslatef(0, 0, 1.5f));
  GL_CHECK(glScalef(2.f, 2.f, 2.f));
  GL_CHECK(glRotatef(-270.f, 1.f, 0, 0));
  glutSolidTeapot(1);
  GL_CHECK(glPopMatrix());
}

