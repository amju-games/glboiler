// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include "object.h"

class renderer : public object
{
public:
    virtual ~renderer() = 0;

    virtual void render() = 0;
};

