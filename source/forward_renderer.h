// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

#include "renderer.h"

class forward_renderer : public renderer
{
public:
  void render(const scene_description&) override;

private:
  void clear_blended_nodes();
  void draw_blended_nodes();
  void depth_pass(const scene_description& sg, const frustum& fr);
  void opaque_pass(const scene_description& sg, const frustum& fr);
  void draw_node(const scene_node& node);
  void draw_children(const scene_node& node);
};

