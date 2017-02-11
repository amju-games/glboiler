// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include "mesh_scene_node.h"

void mesh_scene_node::render_on_gl_thread() const
{
  m_mesh->use_on_gl_thread();
}

//bool mesh_scene_node::load(const std::string& obj_filename)
//{
//  // TODO use res manager, so we upload VAOs on GL thread
//  m_mesh = new ObjMesh;
//  if (m_mesh->Load(obj_filename))
//  {
//    // NO NO NO, just load the meshes and resource names. We upload later in res manager
//    //////m_mesh->upload_on_gl_thread(); // TODO TEMP TEST
//    return true;
//  }
//  return false;
//}

