// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

#include "opengl_includes.h"
#include "teapot_scene_node.h"

void teapot_scene_node::render(int render_flags, const frustum& f) const
{
    glutSolidTeapot(1.0);
}

