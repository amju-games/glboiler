// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include "renderer.h"
#include "render_pass.h"

renderer::~renderer()
{
}

void renderer::render_on_gl_thread()
{
  for (auto p : m_passes)
  {
    p->render_on_gl_thread();
  }
}

void renderer::init_on_gl_thread()
{
  for (auto p : m_passes)
  {
    p->init_on_gl_thread();
  }
}

void renderer::destroy_on_gl_thread()
{
  for (auto p : m_passes)
  {
    p->destroy_on_gl_thread();
  }
}

void renderer::add_pass(std::shared_ptr<render_pass> pass)
{
  pass->set_renderer(this);
  m_passes.push_back(pass);
}