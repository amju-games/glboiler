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

void scene_node::add_render_pass(unsigned int rpt)
{
  m_render_passes |= rpt;
}

bool scene_node::yes_render_in_pass(unsigned int rpt) const
{
  // If zero, the node is never rendered in any pass!
  gl_boiler_assert(m_render_passes != 0);

  return (m_render_passes & rpt) != 0;
}

