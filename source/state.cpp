// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

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

view* state::get_view()
{ 
  return m_renderer->get_view(); 
}

