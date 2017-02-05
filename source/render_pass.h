// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

class renderer;

// Zero-based number for each pass. We store as bit positions in an 
//  int, for each node. This tells us which nodes to render in each pass.
enum class render_pass_type
{
  SHADOW_PASS,
  FORWARD_OPAQUE_PASS,
};

// * pass *
// Render pass base class. Owned by a renderer, to which we have a weak
//  pointer.
class render_pass
{
public:
  // When we construct, point back to the owning renderer (i.e. weak ptr)
  render_pass(renderer* r) : m_renderer(r) {}

  virtual void init_on_gl_thread() = 0;
  virtual void destroy_on_gl_thread() = 0;
  virtual void render_on_gl_thread() = 0;

  renderer* get_renderer() { return m_renderer; }

protected:
  renderer* m_renderer = nullptr; // weak ptr
};

