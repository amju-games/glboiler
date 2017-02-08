// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include "obj_mesh.h"
#include "obj_scene_node.h"

void obj_scene_node::render_on_gl_thread() const
{
  m_mesh->use_on_gl_thread();
}

bool obj_scene_node::load(const std::string& obj_filename)
{
  // TODO use res manager, so we upload VAOs on GL thread
  m_mesh = new ObjMesh;
  if (m_mesh->Load(obj_filename))
  {
    m_mesh->upload_on_gl_thread(); // TODO TEMP TEST
    return true;
  }
  return false;
}

