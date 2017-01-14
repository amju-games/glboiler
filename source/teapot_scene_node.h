// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include "scene_node.h"

class teapot_scene_node : public scene_node
{
public:
  teapot_scene_node();
  virtual void render() const override;
};

