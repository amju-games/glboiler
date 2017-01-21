// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

#include <gtest/gtest.h>
#include "gl_2_renderer.h"

TEST(gl_2_renderer, create)
{
    gl_2_renderer r;
    const render_stats& stats = r.get_render_stats();
    ASSERT_EQ(0, stats.num_nodes_rendered);
}

