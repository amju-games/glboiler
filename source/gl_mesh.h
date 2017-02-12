// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include <memory>
#include <vector>
#include "resource.h"

class scene_node;
class resource_manager;

class gl_mesh : public gl_resource
{
public:
  // Not virtual, different resources have different load functions (e.g. shader)
  ////virtual bool load(const std::string& filename) = 0;

  virtual std::vector<std::shared_ptr<scene_node>> make_scene_nodes(resource_manager& rm) = 0;

private:

};

