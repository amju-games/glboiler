// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

#include <gtest/gtest.h>
#include "mat3.h"
#include "mat4_test_utils.h"

TEST(mat3, ctor_sets_identity)
{
  mat3 m3;
  mat3 expected(1, 0, 0,  0, 1, 0,  0, 0, 1);
  assert_equal(m3, expected);
}

TEST(mat3, create_from_array)
{
  float arr[9] = { 10, 20, 30, 40, 50, 60, 70, 80, 90 };
  mat3 m3(arr); // array ctor
  mat3 expected(10, 20, 30, 40, 50, 60, 70, 80, 90); // uses 9-float ctor
  assert_equal(m3, expected);
}

TEST(mat3, create_from_mat4)
{
  mat4 src = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
  mat3 m3(src);

  mat3 expected = { 1, 2, 3, 5, 6, 7, 9, 10, 11 };
  assert_equal(m3, expected);
}

TEST(mat3, inverse_transpose)
{
  {
    float arr[9] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };
    mat3 m3(arr); // array ctor
    m3.inverse_transpose();
    mat3 expected = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };
    assert_equal(m3, expected);
  }

  {
    float arr[9] = { 2, 0, 0, 0, 2, 0, 0, 0, 2 };
    mat3 m3(arr); // array ctor
    m3.inverse_transpose();
    mat3 expected = { .5f, 0, 0, 0, .5f, 0, 0, 0, .5f };
    assert_equal(m3, expected);
  }

  {
    // Create a mat3 rotation matrix. Compare with the inverse transpose - should be the same.
    mat4 mat4_rotation;
    mat4_rotation.rotate_x_radians(static_cast<float>(M_PI_2));
    mat3 expected(mat4_rotation);
    mat3 after_inverse_transpose(mat4_rotation);
    after_inverse_transpose.inverse_transpose();
    assert_equal(after_inverse_transpose, expected);
  }
}


