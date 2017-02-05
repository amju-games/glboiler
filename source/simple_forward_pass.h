// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include "pass.h"

// * simple_forward_pass *
// Render pass: most basic forward render
class simple_forward_pass : public pass
{
public:
  simple_forward_pass(renderer* r) : pass(r) {}

  virtual void render_on_gl_thread() override;
};

