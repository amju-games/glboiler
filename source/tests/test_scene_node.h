// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include "scene_node.h"

class test_scene_node : public scene_node
{
public:
    virtual void render_on_gl_thread() const override
    {
    }
};

