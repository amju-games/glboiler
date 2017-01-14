// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include "int_graph.h"

void int_graph::add_connection(int node_1, int node_2)
{
  if (m_connections.size() <= node_1)
  {
    // When we resize, increase by more than the bare minimum necessary,
    //  as we are likely to want to add more nodes. I.e. same reasoning
    //  as when we resize in vector::push_back.
    const float RESIZE_FACTOR = 1.5f;

    // Add 1: if node_1 is zero, we want to have space for at least
    //  1 element.
    int new_size = static_cast<int>(node_1 * RESIZE_FACTOR) + 1;
    m_connections.resize(new_size);
  }
  m_connections[node_1].push_back(node_2);
}

std::vector<int> int_graph::get_connections(int node) const
{
  if (m_connections.size() <= node)
  {
    return std::vector<int>();
  }
  return m_connections[node];
}

