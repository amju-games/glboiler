// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

#include <gtest/gtest.h>
#include "frustum.h"
#include "plane.h"

TEST(frustum, create_simplest)
{
  // Identity matrix should give frustum with all planes distance 1, pointing inwards.

  frustum f;
  mat4 m; // identity
  f.set_from_matrix(m);

  plane p = f.get_plane(frustum::FRUSTUM_PLANE_LEFT);
  ASSERT_EQ(p.n, vec3(1, 0, 0));
  ASSERT_EQ(p.d, 1);

  p = f.get_plane(frustum::FRUSTUM_PLANE_RIGHT);
  ASSERT_EQ(p.n, vec3(-1, 0, 0));
  ASSERT_EQ(p.d, 1);

  p = f.get_plane(frustum::FRUSTUM_PLANE_TOP);
  ASSERT_EQ(p.n, vec3(0, -1, 0));
  ASSERT_EQ(p.d, 1);

  p = f.get_plane(frustum::FRUSTUM_PLANE_BOTTOM);
  ASSERT_EQ(p.n, vec3(0, 1, 0));
  ASSERT_EQ(p.d, 1);

  p = f.get_plane(frustum::FRUSTUM_PLANE_NEAR);
  ASSERT_EQ(p.n, vec3(0, 0, 1));
  ASSERT_EQ(p.d, 1);

  p = f.get_plane(frustum::FRUSTUM_PLANE_FAR);
  ASSERT_EQ(p.n, vec3(0, 0, -1));
  ASSERT_EQ(p.d, 1);
}

