// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

#include <gtest/gtest.h>
#include "basic_renderer.h"

TEST(basic_renderer, create)
{
    basic_renderer r;
    const render_stats& stats = r.get_render_stats();
    ASSERT_EQ(0, stats.num_nodes_rendered);
}

