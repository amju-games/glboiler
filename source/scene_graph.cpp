// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include <set>
#include <stack>
#include "boiler_assert.h"
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
  gl_boiler_assert(i < static_cast<int>(m_nodes.size()));
  return *m_nodes[i];
}

std::vector<int> scene_graph::get_connections(int from_node) const
{
  return m_int_graph.get_connections(from_node);
}

void scene_graph::update()
{
  // TODO factor out traversal if we need to do it for anything else
  if (m_int_graph.is_empty())
  {
    return;
  }

  // In this traversal, visit each node once.
  std::stack<int> to_visit;
  std::set<int> visited;
  int root = 0;
  to_visit.push(root);

  while (!to_visit.empty())
  {
    int id = to_visit.top();
    to_visit.pop();

    visited.insert(id);

    scene_node& node = *m_nodes[id]; 
    node.update();

    auto child_ids = get_connections(id);
    for (int ch_id : child_ids)
    {
      if (visited.count(ch_id) == 0)
      {
        to_visit.push(ch_id);
      }
    }
  }
}

