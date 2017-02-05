// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include "render_pass.h"
#include "render_to_texture.h"

// * shadow_pass *
// Render pass: render shadow maps
class shadow_depth_pass : public render_pass
{
public:
  virtual void init_on_gl_thread() override;
  virtual void destroy_on_gl_thread() override;
  virtual void render_on_gl_thread() override;

  render_to_texture* get_shadow_map() { return &m_shadow_map; }
  const mat4& get_light_matrix() const { return m_light_matrix; }

private:
  virtual void draw_node(
    const scene_node& node, 
    const frustum& fr, 
    const mat4& xform) override;

private:
  render_to_texture m_shadow_map;
  gl_shader m_depth_shader;
  mat4 m_light_matrix;
  int m_shadow_map_size = 1024;
};

