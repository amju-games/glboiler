// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include "look_at.h"
#include "projection.h"
#include "renderer.h"
#include "scene_graph.h"
#include "state.h"

void state::set_window_size(int w, int h)
{
  m_window_w = w;
  m_window_h = h;
}

void state::init_on_gl_thread(resource_manager& rm)
{
  // Create renderers
  create_renderers_on_gl_thread();

  // Create scene graph
  set_up_scene_graph_on_gl_thread(rm);
}

void state::destroy_on_gl_thread()
{
  m_sg.reset(nullptr);
  m_renderers.clear();
}

void state::render_on_gl_thread() const
{
  for (auto& rend : m_renderers)
  {
    rend->begin_render_on_gl_thread(*m_sg);

    rend->render_on_gl_thread(0);

    rend->end_render_on_gl_thread();
  }
}

void state::update(float dt)
{
  m_sg->update(dt);
}

void state::set_up_renderer_on_gl_thread(renderer& rend, int x, int y, int w, int h, bool left_side)
{
  rend.init_on_gl_thread();

  camera left_cam, right_cam;
  float eye_sep = 0.5f;
  float y_dist = 10.f;
  float z_dist = 20.0f;
  vec3 left(-eye_sep, y_dist, z_dist);
  vec3 right(eye_sep, y_dist, z_dist);
  vec3 up(0, 1, 0);
  look_at(left, -left, up).set_matrix(left_cam.look_at_matrix);
  look_at(right, -right, up).set_matrix(right_cam.look_at_matrix);

  perspective p(45.0f, 1.0f, 0.1f, 10000.0f);
  p.set_matrix(left_cam.proj_matrix);
  p.set_matrix(right_cam.proj_matrix);

  if (left_side)
  {
    rend.set_view(0, view(viewport(0, 0, w / 2, h), left_cam));
  }
  else
  {
    rend.set_view(0, view(viewport(w / 2, 0, w / 2, h), right_cam));
  }
}

