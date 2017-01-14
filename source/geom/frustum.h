// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include "mat4.h"

class frustum
{
public:
  frustum();
  void set_from_matrix(mat4 m);

private:
  float m_planes[6][4];
};

