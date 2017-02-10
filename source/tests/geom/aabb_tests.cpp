// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

#include <gtest/gtest.h>
#include "aabb.h"

TEST(aabb, create_default)
{
  aabb a;
  ASSERT_EQ(a.get_min(), vec3(0, 0, 0));
  ASSERT_EQ(a.get_max(), vec3(0, 0, 0));
}

TEST(aabb, create)
{
  aabb a(vec3(1, 2, 3), vec3(4, 5, 6));
  ASSERT_EQ(a.get_min(), vec3(1, 2, 3));
  ASSERT_EQ(a.get_max(), vec3(4, 5, 6));
}

// TODO Intersection, union

