// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include "render_pass.h"
#include "render_pass_type.h"
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

  render_stats& get_render_stats() { return m_render_stats; }

  void set_view(const view& v) { m_view = v; }
  view* get_view() { return &m_view; }

  const scene_graph& get_scene_graph() const { return *m_sg; }

protected:
  void add_pass(std::shared_ptr<render_pass> pass);

protected:
  // Point to scene graph we are currently rendering. 
  // Should be set in begin_render_on_gl_thread(), cleared in end_render_on_gl_thread().
  const scene_graph* m_sg = nullptr;

  // Render passes.
  // Useful some of the time, but not when we need to know the specifics of each pass.
  std::vector<std::shared_ptr<render_pass>> m_passes;

  render_stats m_render_stats;
  view m_view;
};

