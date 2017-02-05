// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include "render_pass.h"

class shadow_opaque_pass : public render_pass
{
public:
  virtual void render_on_gl_thread() override;
  virtual void init_on_gl_thread() override;
  virtual void destroy_on_gl_thread() override;

  // Set light matrix from shadow depth pass
  // (Currently there is only one shadow map)
  void set_light_matrix(const mat4& m) { m_light_matrix = m; }

  // Set the shadow map we rendered in the shadow depth pass
  // (Currently there is only one shadow map)
  void set_shadow_map(render_to_texture* shadow_map) { m_shadow_map = shadow_map; }

private:
  virtual void draw_node(
    const scene_node& node, 
    const frustum& fr, 
    const mat4& xform) override;

private:
  render_to_texture* m_shadow_map = nullptr;
  gl_shader m_opaque_pass_shader;  
  mat4 m_light_matrix;

};