// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include "renderer.h"

// * gl_1_1_renderer *
// GL 1.1 - style renderer, for comparison/control.
class gl_1_1_renderer : public renderer
{
public:
  virtual void render_on_gl_thread(int view_index) override;

protected:
  virtual void draw_node(
    const scene_node& node, 
    const frustum& fr, 
    gl_shader* override_shader, 
    const mat4& xform) override;
};

