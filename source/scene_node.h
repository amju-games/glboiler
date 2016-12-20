// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include <memory>
#include "object.h"

class frustum;

class scene_node : public object
{
public:
    virtual void render(int render_flags, const frustum& f) const = 0;
};

using p_scene_node = std::shared_ptr<scene_node>;

