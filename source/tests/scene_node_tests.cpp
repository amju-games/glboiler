// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

#include <gtest/gtest.h>
#include "test_scene_node.h"
#include "frustum.h"
#include "mat4_test_utils.h"

TEST(scene_node, render)
{
  test_scene_node n;
  n.render();
}

TEST(scene_node, initial_xform)
{
  test_scene_node n;
  assert_identity(n.get_world_xform());
}

TEST(scene_node, change_xform)
{
  test_scene_node n;
  mat4 m2 = { 1, 2, 3, 4,  5, 6, 7, 8,  9, 10, 11, 12,  13, 14, 15, 16 };
  mat4 result;
  mult(n.get_world_xform(), m2, result);
  assert_equal(result, m2);

  ASSERT_TRUE(n.has_changed());
}


