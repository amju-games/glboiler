// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include <memory>
#include "renderer.h"
#include "scene_graph.h"
#include "state.h"

class md3_state : public state
{
public:

protected:
  virtual void create_renderers_on_gl_thread() override;
  virtual void set_up_scene_graph_on_gl_thread(resource_manager& rm);

};

