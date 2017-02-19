// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include "boiler_assert.h"
#include "scene_node.h"

scene_node::scene_node()
{
  // By default, use volume that always reports as being partially inside 
  //  the frustum
  m_bounding_vol.reset(new bounding_vol);
}

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

const bounding_vol& scene_node::get_bounding_vol() const
{
  gl_boiler_assert(m_bounding_vol.get());
  return *m_bounding_vol;
}

