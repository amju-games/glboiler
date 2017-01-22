// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include <stack>
#include "renderer.h"

renderer::~renderer()
{
}

struct traversal_node
{
  traversal_node() = default;
  traversal_node(int id_) : id(id_) {}
  traversal_node(int id_, const mat4& m) : id(id_), combined_matrix(m) {}

  int id = -1;
  mat4 combined_matrix;
};

void renderer::traverse(
  const scene_graph& sg,
  const frustum& fr,
  gl_shader* override_shader)
{
  // In this traversal we can visit the same node more than once - required for reflections.
  // It's ok as long as there is not a cycle in the graph.

  std::stack<traversal_node> to_visit;
  int root = 0;
  to_visit.push(root);

  while (!to_visit.empty())
  {
    const auto& tn = to_visit.top();
    to_visit.pop();

    const scene_node& node = sg.get_node(tn.id);
    mat4 m = mult(tn.combined_matrix, node.get_xform());
    draw_node(node, fr, override_shader, m);

    auto child_ids = sg.get_connections(tn.id);
    for (int ch_id : child_ids)
    {
      to_visit.push(traversal_node(ch_id, m));
    }
  }
}



