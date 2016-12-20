// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

#include <gtest/gtest.h>
#include "scene_graph.h"
#include "test_scene_node.h"

TEST(scene_graph, create)
{
    scene_graph sg;
}

TEST(scene_graph, add_node)
{
    scene_graph sg;
    p_scene_node n(new test_scene_node);
    sg.add_node(n);
}

TEST(scene_graph, add_connections)
{
    scene_graph sg;
    p_scene_node node_1(new test_scene_node);
    p_scene_node node_2(new test_scene_node);

    int id_1 = sg.add_node(node_1);
    int id_2 = sg.add_node(node_2);

    sg.add_connection(id_1, id_2);
}

