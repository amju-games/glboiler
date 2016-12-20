// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include <vector>
#include "object.h"
#include "scene_node.h"

class scene_graph : public object
{
public:
    // Add a scene node to the scene graph.
    // Returns ID of scene node.
    int add_node(p_scene_node node);

    // Add connection between two nodes in the graph. The params are IDs
    //  which would have been returned by add_node() when the nodes were
    //  added to the graph.
    void add_connection(int node_1, int node_2);

private:
    using node_vec = std::vector<p_scene_node>;
    node_vec m_nodes;

    using connection_vec = std::vector<std::vector<int>>;
    connection_vec m_connections;
};

