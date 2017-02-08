// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include "obj_mesh.h"
#include "scene_node.h"

class obj_scene_node : public scene_node
{
public:
  virtual void render_on_gl_thread() const override;

  bool load(const std::string& obj_filename);

private:
  ObjMesh* m_mesh = nullptr;

};

