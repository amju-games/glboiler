// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include "object.h"
#include "scene_graph.h"
#include "view.h"

struct render_stats
{
  int num_nodes_rendered = 0;
};

class renderer : public object
{
public:
  virtual ~renderer() = 0;
  
  virtual void init_on_gl_thread() {}
  virtual void render_on_gl_thread(const scene_graph& sg) = 0;

  const render_stats& get_render_stats() const { return m_render_stats; }

  void set_view(int n, const view& v) { m_view[n] = v; }

protected:
  render_stats m_render_stats;
  static const int MAX_NUM_VIEWPORTS = 2;
  view m_view[MAX_NUM_VIEWPORTS];
  std::vector<scene_node*> m_blended_nodes;
};

