// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

#include "renderer.h"
#include "render_to_texture.h"

class forward_renderer : public renderer
{
public:
  void init_on_gl_thread() override;
  void render_on_gl_thread(const scene_description&) override;

private:
  void clear_blended_nodes();
  void draw_blended_nodes(const frustum& fr);
  void shadow_map_pass(const scene_description& sg);
  void opaque_pass(const scene_description& sg, const frustum& fr);
  void draw_node(const scene_node& node, const frustum& fr);
  void draw_children(const scene_node& node, const frustum& fr);

private:
  render_to_texture m_shadow_map;
};

