// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include "resource.h"
#include "scene_node.h"

class mesh_scene_node : public scene_node
{
public:
  mesh_scene_node();

  virtual void render_on_gl_thread() const override;

  void set_mesh(std::shared_ptr<gl_resource> mesh);

private:
  // Owned by resource manager
  std::shared_ptr<gl_resource> m_mesh;

};

