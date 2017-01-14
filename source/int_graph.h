// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include <vector>

// Directed graph of ints.
// The ints are used here as scene node IDs in a scene graph.
class int_graph
{
public:
  void add_connection(int from_node, int to_node);

  bool is_empty() const { return m_connections.empty(); }

  std::vector<int> get_connections(int from_node) const;
 
private:
  using connection_vec = std::vector<std::vector<int>>;
  connection_vec m_connections;
};

