// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include <memory>
#include <vector>
#include "scene_graph.h"
#include "renderer.h"

class resource_manager;

class view;

class state
{
public:
  virtual ~state() = default;

  virtual void init_on_gl_thread(resource_manager& rm);
  virtual void destroy_on_gl_thread();

  virtual void on_enter() {}
  virtual void on_exit() {}

  virtual void render_on_gl_thread() const;
  virtual void update(float dt);

  void set_window_size(int w, int h);

  view* get_view(); 

protected:
  virtual void set_up_scene_graph_on_gl_thread(resource_manager& rm) = 0;

  virtual void create_renderer_on_gl_thread(resource_manager& rm) = 0;

protected:
  int m_window_w = 1;
  int m_window_h = 1;

  // The scene graph we are rendering in this state
  std::unique_ptr<scene_graph> m_sg;

  // Renders the scene graph
  std::unique_ptr<renderer> m_renderer;
};

