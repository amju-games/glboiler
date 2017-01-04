// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

#include <gtest/gtest.h>
#include "colour.h"

TEST(colour, default_ctor)
{
  colour c;
  ASSERT_EQ(c.r, 1);
  ASSERT_EQ(c.g, 1);
  ASSERT_EQ(c.b, 1);
  ASSERT_EQ(c.a, 1);
}

TEST(colour, ctor)
{
  colour c(2, 3, 4, 5);
  ASSERT_EQ(c.r, 2);
  ASSERT_EQ(c.g, 3);
  ASSERT_EQ(c.b, 4);
  ASSERT_EQ(c.a, 5);
}

TEST(colour, mult)
{
  colour c1(1, 2, 3, 4);
  colour c2(6, 7, 8, 9);
  colour c = c1 * c2;
  ASSERT_EQ(c.r, 6);
  ASSERT_EQ(c.g, 14);
  ASSERT_EQ(c.b, 24);
  ASSERT_EQ(c.a, 36);
}

