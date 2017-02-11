// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include "mesh_scene_node.h"

void mesh_scene_node::render_on_gl_thread() const
{
  m_mesh->use_on_gl_thread();
}

