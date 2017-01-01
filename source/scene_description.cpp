// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

#include "scene_description.h"

const scene_node& scene_description::get_root_node() const
{
  return *m_root_node;
}

void scene_description::set_root_node(p_scene_node node)
{
  m_root_node = node;
}

