// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

#include <gtest/gtest.h>
#include "vec3.h"

TEST(vec3, create_default)
{
  vec3 v;
  ASSERT_EQ(0, v.x);
  ASSERT_EQ(0, v.y);
  ASSERT_EQ(0, v.z);
}

TEST(vec3, create)
{
  vec3 v(1, 2, 3);
  ASSERT_EQ(1, v.x);
  ASSERT_EQ(2, v.y);
  ASSERT_EQ(3, v.z);
}

TEST(vec3, equal)
{
  ASSERT_EQ(vec3(1, 1, 1), vec3(1, 1, 1));
  ASSERT_TRUE(vec3(1, 1, 1) == vec3(1, 1, 1));
}

TEST(vec3, dot)
{
  ASSERT_EQ(0, dot(vec3(0, 0, 1), vec3(1, 0, 0)));
  ASSERT_EQ(1, dot(vec3(0, 0, 1), vec3(0, 0, 1)));
  ASSERT_EQ(32, dot(vec3(1, 2, 3), vec3(4, 5, 6)));
}

TEST(vec3, squared_length)
{
  ASSERT_EQ(0, squared_length(vec3(0, 0, 0)));
  ASSERT_EQ(1, squared_length(vec3(0, 1, 0)));
  ASSERT_EQ(25, squared_length(vec3(5, 0, 0)));
  ASSERT_EQ(25, squared_length(vec3(3, 0, 4)));
}

TEST(vec3, length)
{
  ASSERT_EQ(0, length(vec3(0, 0, 0)));
  ASSERT_EQ(1, length(vec3(0, 1, 0)));
  ASSERT_EQ(5, length(vec3(5, 0, 0)));
  ASSERT_EQ(5, length(vec3(3, 0, 4)));
}

TEST(vec3, cross)
{
  ASSERT_EQ(vec3(0, 0,  1), cross(vec3(1, 0, 0), vec3(0, 1, 0)));
  ASSERT_EQ(vec3(0, 0, -1), cross(vec3(0, 1, 0), vec3(1, 0, 0)));

  ASSERT_EQ(vec3( 1, 0, 0), cross(vec3(0, 1, 0), vec3(0, 0, 1)));
  ASSERT_EQ(vec3(-1, 0, 0), cross(vec3(0, 0, 1), vec3(0, 1, 0)));
}

TEST(vec3, normalise)
{
  const float error = 0.000001f;
  ASSERT_NEAR(1, length(normalise(vec3(1, 0, 0))), error);
  ASSERT_NEAR(1, length(normalise(vec3(1, 2, 3))), error);
  ASSERT_NEAR(1, length(normalise(vec3(10, 20, 30))), error);
}

TEST(vec3, plus)
{
  ASSERT_EQ(vec3(0, 0, 0), vec3(0, 0, 0) + vec3(0, 0, 0));
  ASSERT_EQ(vec3(1, 1, 1), vec3(0, 0, 0) + vec3(1, 1, 1));
  ASSERT_EQ(vec3(2, 3, 4), vec3(1, 2, 3) + vec3(1, 1, 1));
  ASSERT_EQ(vec3(2, 3, 4), vec3(1, 1, 1) + vec3(1, 2, 3));
}

TEST(vec3, sub)
{
  ASSERT_EQ(vec3( 0,  0,  0), vec3(0, 0, 0) - vec3(0, 0, 0));
  ASSERT_EQ(vec3(-1, -1, -1), vec3(0, 0, 0) - vec3(1, 1, 1));
  ASSERT_EQ(vec3( 0,  1,  2), vec3(1, 2, 3) - vec3(1, 1, 1));
  ASSERT_EQ(vec3( 0, -1, -2), vec3(1, 1, 1) - vec3(1, 2, 3));
}

TEST(vec3, unary_minus)
{
  ASSERT_EQ(-vec3(0, 0, 0), vec3( 0,  0,  0)); 
  ASSERT_EQ(-vec3(1, 0, 0), vec3(-1,  0,  0)); 
  ASSERT_EQ(-vec3(0, 1, 0), vec3( 0, -1,  0)); 
  ASSERT_EQ(-vec3(0, 0, 1), vec3( 0,  0, -1)); 
  ASSERT_EQ(-vec3(4, 5, 6), vec3(-4, -5, -6)); 
  ASSERT_EQ(-vec3(-4, -5, -6), vec3(4, 5, 6)); 
}


