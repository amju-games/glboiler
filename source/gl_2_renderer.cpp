// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include "gl_2_renderer.h"
#include "gl_includes.h"
#include "gl_shader.h"
#include "light.h"
#include "log.h"
#include "look_at.h"
#include "projection.h"
#include "shadow_depth_pass.h"
#include "opaque_pass.h"

gl_2_renderer::gl_2_renderer()
{
  m_shadow_depth_pass.reset(new shadow_depth_pass);
  m_opaque_pass.reset(new opaque_pass);

  // Store these in a generic vec so we can initialise all the passes etc in the base class.
  add_pass(m_shadow_depth_pass);
  add_pass(m_opaque_pass);
}

void gl_2_renderer::begin_render_on_gl_thread(const scene_graph& sg)
{
  renderer::begin_render_on_gl_thread(sg);
}

void gl_2_renderer::render_on_gl_thread()
{
  m_shadow_depth_pass->render_on_gl_thread();

  // Pass data from one pass to the next
  m_opaque_pass->set_shadow_map(m_shadow_depth_pass->get_shadow_map());
  m_opaque_pass->set_light_matrix(m_shadow_depth_pass->get_light_matrix());

  m_opaque_pass->render_on_gl_thread();
}

void gl_2_renderer::end_render_on_gl_thread()
{
  // Get shadow depth map from first pass
  render_to_texture* shadow_map = m_shadow_depth_pass->get_shadow_map();

  // Draw it on current framebuffer at top right corner, for debugging
  shadow_map->use_texture_on_gl_thread();
  shadow_map->debug_draw_on_gl_thread();

  // Set culling back to default winding order, so external code (open vr) will 
  //  work properly
  GL_CHECK(glFrontFace(GL_CCW));

  renderer::end_render_on_gl_thread();
}
