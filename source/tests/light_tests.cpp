// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

#include <gtest/gtest.h>
#include "light.h"
#include "log.h"
#include "look_at.h"
#include "mat4_test_utils.h"
#include "projection.h"

TEST(directional_light, create)
{
  directional_light light(vec3(2, 3, 4), vec3(5, 6, 7));
  ASSERT_EQ(light.get_pos(), vec3(2, 3, 4));
  ASSERT_EQ(light.get_dir(), vec3(5, 6, 7));
}

TEST(directional_light, matrix)
{
  vec3 pos(2, 3, 4);
  vec3 dir(5, 6, 7);
  directional_light light(pos, dir);
  float size = 1;
  float near_dist = 1;
  float far_dist = 2;
  light.calc_matrix(size, near_dist, far_dist);
  const mat4& m = light.get_matrix();

#ifdef LOG_MATRICES
  log("light matrix:");
  log(m);
#endif // LOG_MATRICES

  // Create matrix which should be the same
  mat4 look_matrix;
  look_at look(pos, dir, vec3(0, 1, 0));
  look.set_matrix(look_matrix);
  mat4 proj;
  ortho o(-size, size, -size, size, near_dist, far_dist);
  o.set_matrix(proj);
  mat4 expected;
  mult(look_matrix, proj, expected);

#ifdef LOG_MATRICES
  log("expected:");
  log(expected);
#endif // LOG_MATRICES

  assert_equal(m, expected);  
}



