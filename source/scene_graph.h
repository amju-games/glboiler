// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include "int_graph.h"
#include "object.h"
#include "scene_node.h"

class scene_graph : public object
{
public:
  // Add a scene node to the scene graph.
  // Returns ID of scene node.
  int add_node(p_scene_node node);

  const scene_node& get_node(int i) const;

  // Add connection between two nodes in the graph. The params are IDs
  //  which would have been returned by add_node() when the nodes were
  //  added to the graph.
  void add_connection(int from_node, int to_node);

  std::vector<int> get_connections(int from_node) const;

  void update();

private:
  using node_vec = std::vector<p_scene_node>;
  node_vec m_nodes;

  int_graph m_int_graph;
};

