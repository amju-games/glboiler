// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include "render_pass_type.h"
#include "resource_manager.h"

class frustum;
class gl_shader;
class mat4;
class renderer;
class scene_graph;
class scene_node;

// * render_pass *
// Render pass base class. Owned by a renderer, to which we have a weak
//  pointer.
class render_pass
{
public:
  // When we construct, point back to the owning renderer (i.e. weak ptr)
  void set_renderer(renderer* r) { m_renderer = r; }

  virtual void init_on_gl_thread(resource_manager& rm) = 0;
  virtual void destroy_on_gl_thread() = 0;
  virtual void render_on_gl_thread() = 0;

  renderer* get_renderer() { return m_renderer; }

protected:
  // Traverse the scene, rendering the nodes which should be rendered 
  //  for the given pass type.
  void traverse_scene_for_pass(
    render_pass_type pass,
    const frustum&);

  virtual void draw_node(
    const scene_node& node,
    const frustum& fr,
    const mat4& combined_ancestor_xform) = 0;

protected:
  renderer* m_renderer = nullptr; // weak ptr
};

