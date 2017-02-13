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
  create_renderer_on_gl_thread(rm);

  // Create scene graph
  set_up_scene_graph_on_gl_thread(rm);
}

void state::destroy_on_gl_thread()
{
  m_sg.reset(nullptr);
  m_renderer.reset(nullptr);
}

void state::render_on_gl_thread() const
{
  m_renderer->begin_render_on_gl_thread(*m_sg);
  m_renderer->render_on_gl_thread();
  m_renderer->end_render_on_gl_thread();
}

void state::update(float dt)
{
  m_sg->update(dt);
}

void state::set_up_renderer_on_gl_thread(renderer& rend, int x, int y, int w, int h, resource_manager& rm)
{
  rend.init_on_gl_thread(rm);

  vec3 eye_pos(0, 80, 200); // TODO TEMP TEST
  const vec3 up(0, 1, 0);

  perspective p(45.0f, 1.0f, 0.1f, 10000.0f);

  camera cam;
  p.set_matrix(cam.proj_matrix);
  look_at(eye_pos, -eye_pos, up).set_matrix(cam.look_at_matrix);
  rend.set_view(view(viewport(0, 0, w / 2, h), cam));
}

view* state::get_view()
{ 
  return m_renderer->get_view(); 
}

