// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

#include <iostream>
#include <gtest/gtest.h>
#include "mat4_test_utils.h"

void log(const mat4 m)
{
  std::string t = "\t";
  std::string n = "\n";
  std::cout
    << m[0] << t << m[4] << t << m[8]  << t << m[12] << n
    << m[1] << t << m[5] << t << m[9]  << t << m[13] << n
    << m[2] << t << m[6] << t << m[10] << t << m[14] << n
    << m[3] << t << m[7] << t << m[11] << t << m[15] << n;
}

void assert_identity(const mat4 m)
{
  ASSERT_EQ(m[0],  1);
  ASSERT_EQ(m[1],  0);
  ASSERT_EQ(m[2],  0);
  ASSERT_EQ(m[3],  0);
  ASSERT_EQ(m[4],  0);
  ASSERT_EQ(m[5],  1);
  ASSERT_EQ(m[6],  0);
  ASSERT_EQ(m[7],  0);
  ASSERT_EQ(m[8],  0);
  ASSERT_EQ(m[9],  0);
  ASSERT_EQ(m[10], 1);
  ASSERT_EQ(m[11], 0);
  ASSERT_EQ(m[12], 0);
  ASSERT_EQ(m[12], 0);
  ASSERT_EQ(m[13], 0);
  ASSERT_EQ(m[14], 0);
  ASSERT_EQ(m[15], 1);
}

void assert_equal(const mat4 m1, const mat4 m2)
{
  float e = 0.00001f;
  ASSERT_NEAR(m1[0],  m2[0],  e);
  ASSERT_NEAR(m1[1],  m2[1],  e);
  ASSERT_NEAR(m1[2],  m2[2],  e);
  ASSERT_NEAR(m1[3],  m2[3],  e);
  ASSERT_NEAR(m1[4],  m2[4],  e);
  ASSERT_NEAR(m1[5],  m2[5],  e);
  ASSERT_NEAR(m1[6],  m2[6],  e);
  ASSERT_NEAR(m1[7],  m2[7],  e);
  ASSERT_NEAR(m1[8],  m2[8],  e);
  ASSERT_NEAR(m1[9],  m2[9],  e);
  ASSERT_NEAR(m1[10], m2[10], e);
  ASSERT_NEAR(m1[11], m2[11], e);
  ASSERT_NEAR(m1[12], m2[12], e);
  ASSERT_NEAR(m1[13], m2[13], e);
  ASSERT_NEAR(m1[14], m2[14], e);
  ASSERT_NEAR(m1[15], m2[15], e);
}


