// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include <memory>
#include <vector>

class resource_manager;
class renderer;
class scene_graph;

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

  view* get_view() { return m_renderers[0]->get_view(0); }

protected:
  virtual void set_up_scene_graph_on_gl_thread(resource_manager& rm) = 0;

  virtual void create_renderers_on_gl_thread() = 0;

  // Convenience function for setting up stereo renderers, offsets by eye distance
  static void set_up_renderer_on_gl_thread(renderer& rend, int x, int y, int w, int h, bool left_side);

protected:
  bool m_is_stereo = false;
  int m_window_w = 1;
  int m_window_h = 1;

  // The scene graph we are rendering in this state
  std::unique_ptr<scene_graph> m_sg;

  // Renders the scene graph
  std::vector<std::shared_ptr<renderer>> m_renderers;
};

