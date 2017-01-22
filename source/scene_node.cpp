// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include "scene_node.h"

void scene_node::set_material(std::shared_ptr<material> material)
{
  m_material = material;
}

void scene_node::use_material_on_gl_thread() const
{
  if (m_material)
  {
    m_material->use_on_gl_thread();
  }
}

