// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include "state.h"

class obj_state : public state
{
public:
  virtual void init_on_gl_thread(resource_manager& rm) override;

protected:
  virtual void create_renderer_on_gl_thread(resource_manager& rm) override;
  virtual void set_up_scene_graph_on_gl_thread(resource_manager& rm) override;
};

