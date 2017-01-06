// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

#include <assert.h>
#include "scene_graph.h"

int scene_graph::add_node(p_scene_node node)
{
  int id = m_nodes.size();
  m_nodes.push_back(node);
  node->set_id(id);
  return id;
}

void scene_graph::add_connection(int from_node, int to_node)
{
  m_int_graph.add_connection(from_node, to_node);
}

const scene_node& scene_graph::get_node(int i) const
{
  assert(i < m_nodes.size());
  return *m_nodes[i];
}

std::vector<int> scene_graph::get_connections(int from_node) const
{
  return m_int_graph.get_connections(from_node);
}

