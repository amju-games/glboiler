// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

#include <iostream>
#include <gtest/gtest.h>
#include "gl_includes.h"
#include "look_at.h"
#include "mat4_test_utils.h"
#include "projection.h"
#include "vec3.h"

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
  glPushMatrix();
  glLoadIdentity();
  vec3 eye(4, 5, 6);
  vec3 dir(7, 8, 9);
  vec3 up(1, 2, 3);
  vec3 target(eye + dir);
  gluLookAt(eye.x, eye.y, eye.z,  target.x, target.y, target.z,  up.x, up.y, up.z);
  mat4 ogl_result;
  glGetFloatv(GL_MODELVIEW_MATRIX, ogl_result);
  glPopMatrix();
 
  mat4 look_at_result;
  look_at look(eye, dir, up);
  look.set_matrix(look_at_result);

  std::cout << "gluLookAt:\n";
  log(ogl_result);
  std::cout << "look_at:\n";
  log(look_at_result);

  assert_equal(look_at_result, ogl_result);
}

TEST(perspective, same_as_glu_perspective)
{
  // Requires OpenGL context to be created  

  mat4 persp_result;
  perspective p(5, 6, 7, 8);
  p.set_matrix(persp_result);

  glMatrixMode(GL_MODELVIEW_MATRIX);
  glPushMatrix();
  glLoadIdentity();
  gluPerspective(5, 6, 7, 8);
  mat4 ogl_result;
  glGetFloatv(GL_MODELVIEW_MATRIX, ogl_result);
  glPopMatrix();

  std::cout << "gluPerspective:\n";
  log(ogl_result);
  std::cout << "perspective:\n";
  log(persp_result);

  assert_equal(persp_result, ogl_result);
}

