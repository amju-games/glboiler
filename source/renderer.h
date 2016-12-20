// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include "object.h"

struct render_stats
{
    render_stats() : 
        num_nodes_rendered(0)
        {}

    int num_nodes_rendered;
};

class renderer : public object
{
public:
    virtual ~renderer() = 0;

    virtual void render() = 0;

    const render_stats& get_render_stats() const { return m_render_stats; }

protected:
    render_stats m_render_stats;
};

