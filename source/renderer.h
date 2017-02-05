// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include "render_pass.h"
#include "scene_graph.h"
#include "view.h"

class gl_shader;

struct render_stats
{
  int num_nodes_rendered = 0;
};

class renderer 
{
public:
  virtual ~renderer() = 0;
  
  // One-time initialisation. 
  // Default behaviour is to initialise all render passes.
  virtual void init_on_gl_thread();
  
  // Render: begin, render for each view, then end.
  virtual void begin_render_on_gl_thread(const scene_graph& sg) { m_sg = &sg; }
  virtual void render_on_gl_thread();
  virtual void end_render_on_gl_thread() { m_sg = nullptr; }

  // Final clean up
  // Default behaviour is to destroy all render passes.
  virtual void destroy_on_gl_thread();

  const render_stats& get_render_stats() const { return m_render_stats; }

  void set_view(const view& v) { m_view = v; }
  view* get_view() { return &m_view; }

  // Traverse the scene, rendering the nodes which should be rendered 
  //  in the given pass.
  void traverse_scene_for_pass(
    render_pass_type pass, 
    const frustum&, 
    gl_shader* override_shader);

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

  // Render passes. 
  std::vector<std::shared_ptr<render_pass>> m_passes;

  render_stats m_render_stats;
  view m_view;

  // TODO go in blended pass
  std::vector<scene_node*> m_blended_nodes;
};

