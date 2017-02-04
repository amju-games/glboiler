// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include "gl_1_1_renderer.h"
#include "gl_includes.h"

void gl_1_1_renderer::render_on_gl_thread()
{
  GL_CHECK(glEnable(GL_LIGHTING));
  GL_CHECK(glEnable(GL_LIGHT0));
  GLfloat light_direction[] = { 1.0, 1.0, 1.0, 0.0 }; 
  GL_CHECK(glLightfv(GL_LIGHT0, GL_POSITION, light_direction));

  const camera& cam = m_view.get_camera();

  GL_CHECK(glMatrixMode(GL_PROJECTION));
  GL_CHECK(glLoadMatrixf(cam.proj_matrix.data()));
  GL_CHECK(glMatrixMode(GL_MODELVIEW));
  GL_CHECK(glLoadMatrixf(cam.look_at_matrix.data()));

  frustum frust = m_view.calc_frustum();

  GL_CHECK(glEnable(GL_CULL_FACE)); // test
  GL_CHECK(glFrontFace(GL_CW));
  GL_CHECK(glCullFace(GL_BACK));
  GL_CHECK(glEnable(GL_DEPTH_TEST));
  GL_CHECK(glUseProgram(0));

  traverse(*m_sg, frust, nullptr);
}

void gl_1_1_renderer::draw_node(const scene_node& node, const frustum& fr, gl_shader* override_shader, const mat4& xform)
{
  GL_CHECK(glPushMatrix());
  GL_CHECK(glMultMatrixf(xform.data()));
  node.use_material_on_gl_thread();
  node.render_on_gl_thread();
  m_render_stats.num_nodes_rendered++;
  GL_CHECK(glPopMatrix());
}
