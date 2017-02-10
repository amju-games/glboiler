// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include "render_pass.h"

// * simple_forward_pass *
// Render pass: most basic forward render
class simple_forward_pass : public render_pass
{
public:
  virtual void init_on_gl_thread(resource_manager& rm) override {}
  virtual void render_on_gl_thread() override;
  virtual void destroy_on_gl_thread() override {}

protected:
  virtual void draw_node(
    const scene_node& node,
    const frustum& fr,
    const mat4& xform) override;
};

