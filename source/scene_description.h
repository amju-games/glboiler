// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include <vector>
#include "object.h"
#include "scene_node.h"

using scene_node_id = int;

class scene_description : public object
{
public:
  const scene_node& get_root_node() const;
  void set_root_node(p_scene_node node);
 
private:
  p_scene_node m_root_node;
};

