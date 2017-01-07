// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

#include <gtest/gtest.h>
#include "gl_includes.h"
#include "look_at.h"
#include "mat4_test_utils.h"
#include "projection.h"
#include "vec3.h"

TEST(mat4, create)
{
  mat4 m;
  assert_identity(m);
}

TEST(mat4, assign)
{
  mat4 dest;

  mat4 src = { 1, 2, 3, 4,  5, 6, 7, 8,  9, 10, 11, 12,  13, 14, 15, 16 };

  dest = src;
  assert_equal(dest, src);
}

TEST(mat4, mult_identity_1)
{
  mat4 m1;
  mat4 m2;
  mat4 result = mult(m1, m2);
  assert_identity(result);
}

TEST(mat4, mult_identity_2)
{
  mat4 i;
  mat4 m2 = { 1, 2, 3, 4,  5, 6, 7, 8,  9, 10, 11, 12,  13, 14, 15, 16 };
  mat4 result = mult(i, m2);
  assert_equal(result, m2);
}

TEST(mat4, mult_identity_3)
{
  mat4 i;
  mat4 m2 = { 1, 2, 3, 4,  5, 6, 7, 8,  9, 10, 11, 12,  13, 14, 15, 16 };
  mat4 result = mult(m2, i);
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
  mat4 result = mult(m1, m2);
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

TEST(mat4, rotate_y_1)
{
  mat4 m;
  m.rotate_y_radians(0);
  assert_identity(m);
}

TEST(mat4, rotate_y_2)
{
  mat4 m1;
  float a = M_PI * 1.3;
  m1.rotate_y_radians(a);
  mat4 m2;
  m2.rotate_y_radians(-a);
  mat4 i;
  mat4 m = mult(m1, m2);
  assert_equal(m, i);
}

TEST(mat4, rotate_y_3)
{
  mat4 m;
  float a = M_PI * 0.73;
  m.rotate_y_radians(a);
  const mat4 expected = { 
    cosf(a),  0, -sinf(a), 0,  
    0,        1,  0,       0,
    sinf(a),  0,  cosf(a), 0,
    0,        0,  0,       1
  };
  assert_equal(m, expected);
}

TEST(mat4, translate)
{
  mat4 m;
  m.translate(vec3(5, 6, 7));
  mat4 expected = { 1, 0, 0, 0,    0, 1, 0, 0,    0, 0, 1, 0,    5, 6, 7, 1 };
  assert_equal(m, expected);
}

TEST(mat4, same_as_opengl)
{
  mat4 result = mult(m1, m2);

  // Requires OpenGL context to be created  
  glMatrixMode(GL_MODELVIEW_MATRIX); 
 
  glLoadMatrixf(m2.data()); // note order!
  glMultMatrixf(m1.data());
  float f[16];
  glGetFloatv(GL_MODELVIEW_MATRIX, f);
  mat4 ogl_result = f;

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
  float f[16];
  glGetFloatv(GL_MODELVIEW_MATRIX, f);
  mat4 ogl_result = f;
  glPopMatrix();
 
  mat4 look_at_result;
  look_at look(eye, dir, up);
  look.set_matrix(look_at_result);

#ifdef LOG_MATRICES
  log("gluLookAt:");
  log(ogl_result);
  log("look_at:)";
  log(look_at_result);
#endif // LOG_MATRICES

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
  float f[16];
  glGetFloatv(GL_MODELVIEW_MATRIX, f);
  mat4 ogl_result = f;
  glPopMatrix();

#ifdef LOG_MATRICES
  log("gluPerspective:");
  log(ogl_result);
  log("perspective:");
  log(persp_result);
#endif // LOG_MATRICES

  assert_equal(persp_result, ogl_result);
}

TEST(ortho, ctor)
{
  ortho o(4, 5, 6, 7, 8, 9);
  ASSERT_EQ(o.left, 4);
  ASSERT_EQ(o.right, 5);
  ASSERT_EQ(o.bottom, 6);
  ASSERT_EQ(o.top, 7);
  ASSERT_EQ(o.near_distance, 8);
  ASSERT_EQ(o.far_distance, 9);
}

TEST(ortho, same_as_gl_ortho)
{
  mat4 ortho_result;
  ortho o(3, 4, 5, 6, 7, 8);
  o.set_matrix(ortho_result);

  glMatrixMode(GL_MODELVIEW_MATRIX);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(3, 4, 5, 6, 7, 8);
  float f[16];  
  glGetFloatv(GL_MODELVIEW_MATRIX, f);
  mat4 ogl_result = f;
  glPopMatrix();

#ifdef LOG_MATRICES
  log("glOrtho:");
  log(ogl_result);
  log("ortho:");
  log(ortho_result);
#endif

  assert_equal(ortho_result, ogl_result);
}

