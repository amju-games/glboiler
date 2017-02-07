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

void scene_node::add_render_pass(render_pass_type rpt)
{
  if (rpt == render_pass_type::ALL)
  {
    // Set bit for every pass
    m_render_passes = 0xffffffff;
  }
  else
  {
    m_render_passes |= (1 << static_cast<int>(rpt));
  }
}

bool scene_node::yes_render_in_pass(render_pass_type rpt) const
{
  return (m_render_passes & (1 << static_cast<int>(rpt))) != 0;
}

