// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include "mat4.h"
#include "plane.h"

class frustum
{
public:
  frustum();
  void set_from_matrix(mat4 m);

  enum frustum_plane
  {
    FRUSTUM_PLANE_RIGHT,
    FRUSTUM_PLANE_LEFT,
    FRUSTUM_PLANE_TOP,
    FRUSTUM_PLANE_BOTTOM,
    FRUSTUM_PLANE_FAR,
    FRUSTUM_PLANE_NEAR
  };

  plane get_plane(frustum_plane fpl);

private:
  //float m_planes[6][4];
  plane m_planes[6];
};

