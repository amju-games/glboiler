// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include "md3.h"
#include "scene_node.h"

class md3_node : public scene_node
{
public:
  md3_node();
  virtual void render() const override;

private:
  CModelMD3* m_md3_model;
};

