// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

#include <gtest/gtest.h>
#include "test_scene_node.h"
#include "frustum.h"

TEST(scene_node, render)
{
    test_scene_node n;
    n.render();
}

