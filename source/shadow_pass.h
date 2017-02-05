// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include "render_pass.h"
#include "render_to_texture.h"

// * shadow_pass *
// Render pass: render shadow maps
class shadow_pass : public render_pass
{
public:
  shadow_pass(renderer* r) : render_pass(r) {}

  virtual void init_on_gl_thread() override;
  virtual void destroy_on_gl_thread() override;
  virtual void render_on_gl_thread() override;

private:
  render_to_texture m_shadow_map;
  gl_shader m_depth_shader;
  mat4 m_light_matrix;
  int m_shadow_map_size = 1024;
};

