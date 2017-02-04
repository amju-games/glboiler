// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include "gl_shader.h"
#include "renderer.h"
#include "render_to_texture.h"

// * gl_2_renderer *
// Render scene description with shadows.
class gl_2_renderer : public renderer
{
public:
  gl_2_renderer();

  virtual void init_on_gl_thread() override;
  virtual void begin_render_on_gl_thread(const scene_graph& sg) override;
  virtual void render_on_gl_thread() override;
  virtual void end_render_on_gl_thread() override;
  virtual void destroy_on_gl_thread() override;

private:
  void clear_blended_nodes();
  void draw_blended_nodes(const frustum& fr);
  void shadow_map_pass(const scene_graph& sg);
  void opaque_pass(const scene_graph& sg, const frustum& fr, gl_shader* override_shader = nullptr);

  virtual void draw_node(const scene_node& node, const frustum& fr, gl_shader* override_shader, const mat4& xform) override;

private:
  render_to_texture m_shadow_map;
  gl_shader m_depth_shader;
  gl_shader m_opaque_pass_shader;  // TODO this will be replaced by materials on nodes
  mat4 m_light_matrix;
  int m_shadow_map_size;
};

