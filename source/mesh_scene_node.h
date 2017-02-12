// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include "resource.h"
#include "scene_node.h"

class mesh_scene_node : public scene_node
{
public:
  virtual void render_on_gl_thread() const override;

//  bool load(const std::string& obj_filename);

  void set_mesh(std::shared_ptr<gl_resource> mesh) { m_mesh = mesh; }

private:
  // Owned by resource manager
  std::shared_ptr<gl_resource> m_mesh;

};

