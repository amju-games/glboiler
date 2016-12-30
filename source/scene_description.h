// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include <vector>
#include "camera.h"
#include "object.h"
#include "scene_node.h"

using scene_node_id = int;

class scene_description : public object
{
public:
  const camera& get_camera() const;
  const scene_node& get_root_node() const;
  void set_root_node(p_scene_node node);
 
private:
  camera m_camera;
  p_scene_node m_root_node;
};

