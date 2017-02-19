// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include "aabb.h"
#include "mesh_scene_node.h"

mesh_scene_node::mesh_scene_node()
{
  m_bounding_vol.reset(new aabb);
}

void mesh_scene_node::render_on_gl_thread() const
{
  m_mesh->use_on_gl_thread();
}

void mesh_scene_node::set_mesh(std::shared_ptr<gl_resource> mesh)
{ 
  m_mesh = mesh; 
}

