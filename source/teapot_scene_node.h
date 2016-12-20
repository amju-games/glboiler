// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include "scene_node.h"

class teapot_scene_node : public scene_node
{
public:
    virtual void render(int render_flags, const frustum& f) const override;
};

