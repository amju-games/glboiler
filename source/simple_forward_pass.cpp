// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include "simple_forward_pass.h"

simple_forward_pass::void render_on_gl_thread()
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

  get_renderer()->traverse_scene_for_pass(
    render_pass::FORWARD_PASS, frust, nullptr);
}

