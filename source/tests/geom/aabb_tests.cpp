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

TEST(aabb, include)
{
  {
    aabb a;
    a.include(vec3(1, 2, 3));
    ASSERT_EQ(a.get_min(), vec3(0, 0, 0));
    ASSERT_EQ(a.get_max(), vec3(1, 2, 3));
  }

  {
    aabb a;
    a.include(vec3(-1, -2, -3));
    ASSERT_EQ(a.get_min(), vec3(-1, -2, -3));
    ASSERT_EQ(a.get_max(), vec3(0, 0, 0));

    a.include(vec3(1, 2, 3));
    ASSERT_EQ(a.get_min(), vec3(-1, -2, -3));
    ASSERT_EQ(a.get_max(), vec3(1, 2, 3));
  }

  {
    aabb a;
    a.include(vec3(-1, 2, -3));
    ASSERT_EQ(a.get_min(), vec3(-1, 0, -3));
    ASSERT_EQ(a.get_max(), vec3(0, 2, 0));
  }
}

TEST(aabb, union)
{
  {
    aabb a;
    a.include(vec3(1, 2, 3));
    ASSERT_EQ(a.get_min(), vec3(0, 0, 0));
    ASSERT_EQ(a.get_max(), vec3(1, 2, 3));

    aabb b;
    b.include(vec3(-4, -5, -6));
    ASSERT_EQ(b.get_min(), vec3(-4, -5, -6));
    ASSERT_EQ(b.get_max(), vec3(0, 0, 0));

    aabb c = a.union_with(b);
    ASSERT_EQ(c.get_min(), vec3(-4, - 5, -6));
    ASSERT_EQ(c.get_max(), vec3(1, 2, 3));

    aabb d = b.union_with(a);
    ASSERT_EQ(d.get_min(), vec3(-4, -5, -6));
    ASSERT_EQ(d.get_max(), vec3(1, 2, 3));
  }
}

// TODO Intersection

