// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include <stack>
#include "scene_graph.h"
#include "render_pass.h"
#include "renderer.h"

struct traversal_node
{
  traversal_node() = default;
  traversal_node(int id_) : id(id_) {}
  traversal_node(int id_, const mat4& m) : id(id_), combined_matrix(m) {}

  int id = -1;
  mat4 combined_matrix;
};

void render_pass::traverse_scene_for_pass(
  unsigned int pass,
  const frustum& fr)
{
  // In this traversal we can visit the same node more than once.
  // It's ok as long as there is not a cycle in the graph.

  const scene_graph& sg = get_renderer()->get_scene_graph();

  std::stack<traversal_node> to_visit;
  int root = 0;
  to_visit.push(root);

  while (!to_visit.empty())
  {
    const auto& tn = to_visit.top();
    to_visit.pop();

    const scene_node& node = sg.get_node(tn.id);
    if (!node.yes_render_in_pass(pass))
    {
      // Don't render the node in this pass. 
      // Assuming all ancestor nodes have the same pass flags.
      continue;
    }

    mat4 m = mult(tn.combined_matrix, node.get_xform());

    // TODO VFC here, transform node bounding vol and test against frustum.

    get_renderer()->get_render_stats().num_nodes_rendered++;

    draw_node(node, fr, m);

    auto child_ids = sg.get_connections(tn.id);
    for (int ch_id : child_ids)
    {
      to_visit.push(traversal_node(ch_id, m));
    }
  }
}


