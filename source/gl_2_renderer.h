// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include <memory>
#include "gl_shader.h"
#include "renderer.h"
#include "render_to_texture.h"

class shadow_depth_pass;
class shadow_opaque_pass;

// * gl_2_renderer *
// Render scene with a single shadow map.
class gl_2_renderer : public renderer
{
public:
  gl_2_renderer();

  virtual void begin_render_on_gl_thread(const scene_graph& sg) override;
  virtual void render_on_gl_thread() override;
  virtual void end_render_on_gl_thread() override;

private:
  // Explicit pointers to each pass, which are also pushed back into m_passes,
  //  for generic stuff in the base class.
  std::shared_ptr<shadow_depth_pass> m_shadow_depth_pass;
  std::shared_ptr<shadow_opaque_pass> m_shadow_opaque_pass;
};

