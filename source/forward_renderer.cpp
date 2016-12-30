// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

#include "forward_renderer.h"
#include "gl_includes.h"

void forward_renderer::render(const scene_description& sd)
{
  clear_blended_nodes();
  const frustum& frust = sd.get_camera().calc_frustum();

  depth_pass(sd, frust);
  opaque_pass(sd, frust);

  draw_blended_nodes();
}

void forward_renderer::clear_blended_nodes()
{
  m_blended_nodes.clear();
}

void forward_renderer::depth_pass(const scene_description& sd, const frustum& fr)
{
  GL_CHECK(glCullFace(GL_FRONT));

  const scene_node& node = sd.get_root_node();
  cull_result cr = node.get_bounding_vol().calc_cull_result(fr);
  if (cr != cull_result::FRUSTUM_OUTSIDE)
  {
    draw_node(node);
    draw_children(node);
  }
}

void forward_renderer::opaque_pass(const scene_description& sd, const frustum& fr)
{
  GL_CHECK(glCullFace(GL_BACK));

  const scene_node& node = sd.get_root_node();
  cull_result cr = node.get_bounding_vol().calc_cull_result(fr);
  if (cr != cull_result::FRUSTUM_OUTSIDE)
  {
    draw_node(node);
    draw_children(node);
  }
}

void forward_renderer::draw_node(const scene_node& node)
{
}

void forward_renderer::draw_children(const scene_node& node)
{
}

void forward_renderer::draw_blended_nodes()
{
}



