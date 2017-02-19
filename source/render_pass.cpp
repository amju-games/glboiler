// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include <stack>
#include "gl_includes.h"
#include "scene_graph.h"
#include "render_pass.h"
#include "renderer.h"

struct render_traversal_node
{
  render_traversal_node() = default;
  render_traversal_node(int id_) : id(id_) {}
  render_traversal_node(int id_, bool test_frustum_, const mat4& m) : 
    id(id_), test_frustum(test_frustum_), combined_matrix(m) {}

  int id = -1;
  bool test_frustum = true;
  mat4 combined_matrix;
};

void render_pass::traverse_scene_for_pass(
  unsigned int pass,
  const frustum& fr)
{
  // In this traversal we can visit the same node more than once.
  // It's ok as long as there is not a cycle in the graph.

  const scene_graph& sg = get_renderer()->get_scene_graph();

  std::stack<render_traversal_node> to_visit;
  int root = 0;
  to_visit.push(root);

  while (!to_visit.empty())
  {
    const auto tn = to_visit.top();
    to_visit.pop();

    const scene_node& node = sg.get_node(tn.id);
    if (!node.yes_render_in_pass(pass))
    {
      // Don't render the node in this pass. 
      // Assuming all ancestor nodes have the same pass flags.
      continue;
    }

    mat4 m = mult(tn.combined_matrix, node.get_xform());

    bool test_frustum = tn.test_frustum;
    if (test_frustum)
    {
      // VFC: test intersection of node bounding vol and frustum.
      // Transform bounding volume by combined matrix
      std::unique_ptr<bounding_vol> bv(node.get_bounding_vol().transform_by(m));

      cull_result cr = bv->calc_cull_result(fr);
      if (cr == cull_result::FRUSTUM_OUTSIDE)
      {
        // TODO This stat is not much good, as it doesn't count all the culled
        //  descendants! We could add on the number of descendants of this node?
        get_renderer()->get_render_stats().inc_num_nodes_culled_for_pass(pass);
        continue; // skip rendering this node and descendants
      }
      // No need to test descendants against frustum if we are completely inside.
      // Only test descendants if our bounding vol is partially in and partially
      //  out.
      test_frustum = (cr == cull_result::FRUSTUM_INSIDE_AND_OUTSIDE);
    }

    get_renderer()->get_render_stats().inc_num_nodes_rendered_for_pass(pass);

    draw_node(node, fr, m);

    draw_bounding_vol(node, fr, m);

    auto child_ids = sg.get_connections(tn.id);
    for (int ch_id : child_ids)
    {
      to_visit.push(render_traversal_node(ch_id, test_frustum, m));
    }
  }
}

