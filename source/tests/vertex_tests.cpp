// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

#include <gtest/gtest.h>
#include "vertex.h"

TEST(vertex, default_ctor)
{
  vertex v;
  ASSERT_EQ(v.pos, vec3(0, 0, 0));
  ASSERT_EQ(v.normal, vec3(0, 0, 0));
  ASSERT_EQ(v.uv, vec2(0, 0));
  ASSERT_EQ(v.tangent, vec3(0, 0, 0));
}


