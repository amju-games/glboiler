// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

#include <gtest/gtest.h>
#include "viewport.h"

TEST(viewport, create)
{
  viewport vp(0, 0, 20, 10);
  ASSERT_EQ(2, aspect_ratio(vp));
}

