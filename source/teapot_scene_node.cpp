// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

#include "aabb.h"
#include "gl_includes.h"
#include "teapot_scene_node.h"

teapot_scene_node::teapot_scene_node()
{
  m_bounding_vol.reset(new aabb);
}

void teapot_scene_node::render() const
{
    glutSolidTeapot(0.5);
}

