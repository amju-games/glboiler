// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include "object.h"
#include "scene_graph.h"
#include "view.h"

class gl_shader;

struct render_stats
{
  int num_nodes_rendered = 0;
};

class renderer : public object
{
public:
  virtual ~renderer() = 0;
  
  // One-time initialisation
  virtual void init_on_gl_thread() {}
  
  // Render: begin, render for each view, then end.
  virtual void begin_render_on_gl_thread(const scene_graph& sg) { m_sg = &sg; }
  virtual void render_on_gl_thread(int view_index) = 0;
  virtual void end_render_on_gl_thread() { m_sg = nullptr; }

  // Final clean up
  virtual void destroy_on_gl_thread() {}

  const render_stats& get_render_stats() const { return m_render_stats; }

  // TODO allow views to change?
  void set_view(int n, const view& v) { m_view[n] = v; }

protected:
  // Traverse scene graph. Call draw_node() on scene nodes visited.
  void traverse(
    const scene_graph& sg,
    const frustum& fr,
    gl_shader* override_shader);

  virtual void draw_node(
    const scene_node& node, 
    const frustum& fr, 
    gl_shader* override_shader, 
    const mat4& xform) = 0;

protected:
  // Point to scene graph we are currently rendering. 
  // Should be set in begin_render_on_gl_thread(), cleared in end_render_on_gl_thread().
  const scene_graph* m_sg = nullptr;

  render_stats m_render_stats;
  static const int MAX_NUM_VIEWS = 16; 
  view m_view[MAX_NUM_VIEWS];
  std::vector<scene_node*> m_blended_nodes;
};

