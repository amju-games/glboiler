// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

#include <gtest/gtest.h>
#include "vec2.h"

TEST(vec2, create_default)
{
  vec2 v;
  ASSERT_EQ(0, v.x);
  ASSERT_EQ(0, v.y);
}

TEST(vec2, create)
{
  vec2 v(1, 2);
  ASSERT_EQ(1, v.x);
  ASSERT_EQ(2, v.y);
}

TEST(vec2, equal)
{
  ASSERT_EQ(vec2(1, 1), vec2(1, 1));
  ASSERT_TRUE(vec2(1, 1) == vec2(1, 1));
}

TEST(vec2, dot)
{
  ASSERT_EQ(0, dot(vec2(0, 1), vec2(1, 0)));
  ASSERT_EQ(1, dot(vec2(0, 1), vec2(0, 1)));
  ASSERT_EQ(14, dot(vec2(1, 2), vec2(4, 5)));
}

TEST(vec2, squared_length)
{
  ASSERT_EQ(0, squared_length(vec2(0, 0)));
  ASSERT_EQ(1, squared_length(vec2(0, 1)));
  ASSERT_EQ(25, squared_length(vec2(5, 0)));
  ASSERT_EQ(25, squared_length(vec2(3, 4)));
}

TEST(vec2, length)
{
  ASSERT_EQ(0, length(vec2(0, 0)));
  ASSERT_EQ(1, length(vec2(0, 1)));
  ASSERT_EQ(5, length(vec2(5, 0)));
  ASSERT_EQ(5, length(vec2(3, 4)));
}

TEST(vec2, normalise)
{
  const float error = 0.000001f;
  ASSERT_NEAR(1, length(normalise(vec2(1, 0))), error);
  ASSERT_NEAR(1, length(normalise(vec2(2, 3))), error);
  ASSERT_NEAR(1, length(normalise(vec2(10, 20))), error);
}

TEST(vec2, plus)
{
  ASSERT_EQ(vec2(0, 0), vec2(0, 0) + vec2(0, 0));
  ASSERT_EQ(vec2(1, 1), vec2(0, 0) + vec2(1, 1));
  ASSERT_EQ(vec2(2, 3), vec2(1, 2) + vec2(1, 1));
  ASSERT_EQ(vec2(2, 3), vec2(1, 1) + vec2(1, 2));
}

TEST(vec2, sub)
{
  ASSERT_EQ(vec2( 0,  0), vec2(0, 0) - vec2(0, 0));
  ASSERT_EQ(vec2(-1, -1), vec2(0, 0) - vec2(1, 1));
  ASSERT_EQ(vec2( 0,  1), vec2(1, 2) - vec2(1, 1));
  ASSERT_EQ(vec2( 0, -1), vec2(1, 1) - vec2(1, 2));
}

TEST(vec2, unary_minus)
{
  ASSERT_EQ(-vec2(0, 0), vec2( 0,  0)); 
  ASSERT_EQ(-vec2(1, 0), vec2(-1,  0)); 
  ASSERT_EQ(-vec2(0, 1), vec2( 0, -1)); 
  ASSERT_EQ(-vec2(4, 5), vec2(-4, -5)); 
  ASSERT_EQ(-vec2(-5, -6), vec2(5, 6)); 
}


