// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

#include <iostream>
#include <gtest/gtest.h>
#include "gl_includes.h"
#include "look_at.h"
#include "mat4.h"
#include "vec3.h"

void log(mat4 m)
{
  std::string t = "\t";
  std::string n = "\n";
  std::cout 
    << m[0] << t << m[4] << t << m[8]  << t << m[12] << n
    << m[1] << t << m[5] << t << m[9]  << t << m[13] << n
    << m[2] << t << m[6] << t << m[10] << t << m[14] << n
    << m[3] << t << m[7] << t << m[11] << t << m[15] << n;
}

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

TEST(look_at, same_as_glu_look_at)
{
  // Requires OpenGL context to be created  
  // Get gluLookAt matrix
  glMatrixMode(GL_MODELVIEW_MATRIX); 
  glLoadIdentity();
  vec3 eye(4, 5, 6);
  vec3 dir(7, 8, 9);
  vec3 up(1, 2, 3);
  vec3 target(eye + dir);
  gluLookAt(eye.x, eye.y, eye.z,  target.x, target.y, target.z,  up.x, up.y, up.z);
  mat4 ogl_result;
  glGetFloatv(GL_MODELVIEW_MATRIX, ogl_result);
  
  mat4 look_at_result;
  look_at look(eye, dir, up);
  look.set_matrix(look_at_result);

  std::cout << "gluLookAt:\n";
  log(ogl_result);
  std::cout << "look_at:\n";
  log(look_at_result);

  assert_equal(look_at_result, ogl_result);
}



