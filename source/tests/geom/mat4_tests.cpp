// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

#include <gtest/gtest.h>
#include "gl_includes.h"
#include "mat4.h"

void assert_identity(mat4 m)
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
  ASSERT_EQ(m[13], 0);
  ASSERT_EQ(m[14], 0);
  ASSERT_EQ(m[15], 1);
}

void assert_equal(mat4 m1, mat4 m2)
{
  ASSERT_EQ(m1[0],  m2[0]);
  ASSERT_EQ(m1[1],  m2[1]);
  ASSERT_EQ(m1[2],  m2[2]);
  ASSERT_EQ(m1[3],  m2[3]);
  ASSERT_EQ(m1[4],  m2[4]);
  ASSERT_EQ(m1[5],  m2[5]);
  ASSERT_EQ(m1[6],  m2[6]);
  ASSERT_EQ(m1[7],  m2[7]);
  ASSERT_EQ(m1[8],  m2[8]);
  ASSERT_EQ(m1[9],  m2[9]);
  ASSERT_EQ(m1[10], m2[10]);
  ASSERT_EQ(m1[11], m2[11]);
  ASSERT_EQ(m1[12], m2[12]);
  ASSERT_EQ(m1[13], m2[13]);
  ASSERT_EQ(m1[14], m2[14]);
  ASSERT_EQ(m1[15], m2[15]);
}

TEST(mat4, create)
{
  mat4 m;
  load_identity(m);
  assert_identity(m);
}

TEST(mat4, mult_identity_1)
{
  mat4 m1;
  load_identity(m1);
  mat4 m2;
  load_identity(m2);
  mat4 result;
  mult(m1, m2, result);
  assert_identity(result);
}

TEST(mat4, mult_identity_2)
{
  mat4 i;
  load_identity(i);
  mat4 m2 = { 1, 2, 3, 4,  5, 6, 7, 8,  9, 10, 11, 12,  13, 14, 15, 16 };
  mat4 result;
  mult(i, m2, result);
  assert_equal(result, m2);
}

TEST(mat4, mult_identity_3)
{
  mat4 i;
  load_identity(i);
  mat4 m2 = { 1, 2, 3, 4,  5, 6, 7, 8,  9, 10, 11, 12,  13, 14, 15, 16 };
  mat4 result;
  mult(m2, i, result);
  assert_equal(result, m2);
}

static mat4 m1 = {
  1,   2,   3,   4,  
  5,   6,   7,   8,  
  9,   10,  11,  12,  
  13,  14,  15,  16 };

static mat4 m2 = { 
  101, 102, 103, 104,  
  105, 106, 107, 108,  
  109, 110, 111, 112,  
  113, 114, 115, 116 };

TEST(mat4, mult)
{
  mat4 result;
  mult(m1, m2, result);
  mat4 expected = {
    1 * 101 + 2 * 105 + 3 * 109 + 4 * 113,
    1 * 102 + 2 * 106 + 3 * 110 + 4 * 114, 
    1 * 103 + 2 * 107 + 3 * 111 + 4 * 115,
    1 * 104 + 2 * 108 + 3 * 112 + 4 * 116,

    5 * 101 + 6 * 105 + 7 * 109 + 8 * 113,
    5 * 102 + 6 * 106 + 7 * 110 + 8 * 114,
    5 * 103 + 6 * 107 + 7 * 111 + 8 * 115,
    5 * 104 + 6 * 108 + 7 * 112 + 8 * 116,

    9 * 101 + 10 * 105 + 11 * 109 + 12 * 113,
    9 * 102 + 10 * 106 + 11 * 110 + 12 * 114,
    9 * 103 + 10 * 107 + 11 * 111 + 12 * 115,
    9 * 104 + 10 * 108 + 11 * 112 + 12 * 116,

    13 * 101 + 14 * 105 + 15 * 109 + 16 * 113,
    13 * 102 + 14 * 106 + 15 * 110 + 16 * 114,
    13 * 103 + 14 * 107 + 15 * 111 + 16 * 115,
    13 * 104 + 14 * 108 + 15 * 112 + 16 * 116
  };
  assert_equal(result, expected);
}

TEST(mat4, same_as_opengl)
{
  mat4 result;
  mult(m1, m2, result);

  // Requires OpenGL context to be created  
  glMatrixMode(GL_MODELVIEW_MATRIX); 
 
  glLoadMatrixf(m2); // note order!
  glMultMatrixf(m1);
  mat4 ogl_result;
  glGetFloatv(GL_MODELVIEW_MATRIX, ogl_result);

  assert_equal(result, ogl_result);
}


