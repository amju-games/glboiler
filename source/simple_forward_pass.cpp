// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include "gl_includes.h"
#include "renderer.h"
#include "simple_forward_pass.h"

void simple_forward_pass::render_on_gl_thread()
{
  GL_CHECK(glEnable(GL_LIGHTING));
  GL_CHECK(glEnable(GL_LIGHT0));
  GLfloat light_direction[] = { 1.0, 1.0, 1.0, 0.0 };
  GL_CHECK(glLightfv(GL_LIGHT0, GL_POSITION, light_direction));

  view* v = get_renderer()->get_view();
  const camera& cam = v->get_camera();

  GL_CHECK(glMatrixMode(GL_PROJECTION));
  GL_CHECK(glLoadMatrixf(cam.proj_matrix.data()));
  GL_CHECK(glMatrixMode(GL_MODELVIEW));
  GL_CHECK(glLoadMatrixf(cam.look_at_matrix.data()));

  frustum frust = v->calc_frustum();

  GL_CHECK(glEnable(GL_CULL_FACE));
  GL_CHECK(glFrontFace(GL_CW));
  GL_CHECK(glCullFace(GL_BACK));
  GL_CHECK(glEnable(GL_DEPTH_TEST));
  GL_CHECK(glUseProgram(0));

  traverse_scene_for_pass(
    render_pass_type::FORWARD_OPAQUE_PASS, frust);
}

void simple_forward_pass::draw_node(
  const scene_node& node,
  const frustum& fr,
  const mat4& xform)
{
  GL_CHECK(glPushMatrix());
  GL_CHECK(glMultMatrixf(xform.data()));
  node.use_material_on_gl_thread();
  node.render_on_gl_thread();
  GL_CHECK(glPopMatrix());
}
