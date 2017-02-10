// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include "gl_1_1_renderer.h"
#include "gl_includes.h"
#include "simple_forward_pass.h"

gl_1_1_renderer::gl_1_1_renderer()
{
  add_pass(std::shared_ptr<render_pass>(new simple_forward_pass));
}

