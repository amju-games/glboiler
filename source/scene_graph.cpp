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

struct update_traversal_node
{
  update_traversal_node() = default;
  update_traversal_node(int id_) : id(id_) {}
  update_traversal_node(int id_, const mat4& m) : id(id_), combined_matrix(m) {}

  int id = -1;
  mat4 combined_matrix;
};

void scene_graph::update(float dt)
{
  // TODO factor out traversal if we need to do it for anything else
  if (m_int_graph.is_empty())
  {
    return;
  }

  // In this traversal, we assume we visit each node once.
  std::stack<update_traversal_node> to_visit;
  std::set<int> visited;
  int root = 0;
  to_visit.push(root);

  while (!to_visit.empty())
  {
    const auto tn = to_visit.top();
    to_visit.pop();

    int id = tn.id;
    visited.insert(id);

    scene_node& node = *m_nodes[id]; 
    node.update();

    mat4 m = mult(tn.combined_matrix, node.get_xform());

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

