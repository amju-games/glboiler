// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

#include <gtest/gtest.h>
#include "vertex.h"

TEST(vertex, default_ctor)
{
  vert v;
  ASSERT_EQ(v.pos, vec3(0, 0, 0));
  ASSERT_EQ(v.normal, vec3(0, 0, 0));
  ASSERT_EQ(v.uv, vec2(0, 0));
  ASSERT_EQ(v.tangent, vec3(0, 0, 0));
}

TEST(vertex, ctor)
{
  vert v(vec3(1, 2, 3), vec3(4, 5, 6), vec2(7, 8), vec3(9, 10, 11));

  ASSERT_EQ(v.pos, vec3(1, 2, 3));
  ASSERT_EQ(v.normal, vec3(4, 5, 6));
  ASSERT_EQ(v.uv, vec2(7, 8));
  ASSERT_EQ(v.tangent, vec3(9, 10, 11));
}

