// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

#include "forward_renderer.h"
#include "gl_includes.h"

void forward_renderer::init_on_gl_thread()
{
  m_shadow_map.set_render_flags(render_to_texture::RENDER_DEPTH);
  m_shadow_map.set_size(1024, 1024); // test
  m_shadow_map.init_on_gl_thread(); 
}

void forward_renderer::render_on_gl_thread(const scene_description& sd)
{
  clear_blended_nodes();

  // Render shadow map, used for both eyes
  view& this_view = m_view[0];
  this_view.set_gl_viewport();
  shadow_map_pass(sd);

  for (int eye = 0; eye < 2; eye++)
  {
    view& this_view = m_view[eye];
    this_view.set_gl_viewport();

    frustum frust = this_view.calc_frustum();

    // Render opaque geom, for each eye
    opaque_pass(sd, frust);

    // Render blended nodes, for each eye
    draw_blended_nodes(frust);
  }

  m_shadow_map.use_texture_on_gl_thread();
  m_shadow_map.debug_draw_on_gl_thread();
}

void forward_renderer::clear_blended_nodes()
{
  m_blended_nodes.clear();
}

void forward_renderer::shadow_map_pass(const scene_description& sd)
{
  m_shadow_map.begin_on_gl_thread();

  // Get light frustum (for each light which casts shadows?!)
  frustum light_frustum;

  GL_CHECK(glCullFace(GL_FRONT));

  const scene_node& node = sd.get_root_node();
  cull_result cr = node.get_bounding_vol().calc_cull_result(light_frustum);
  if (cr != cull_result::FRUSTUM_OUTSIDE)
  {
    draw_node(node, light_frustum);
    draw_children(node, light_frustum);
  }

  m_shadow_map.end_on_gl_thread();
}

void forward_renderer::opaque_pass(const scene_description& sd, const frustum& fr)
{
  GL_CHECK(glCullFace(GL_BACK));

  const scene_node& node = sd.get_root_node();
  cull_result cr = node.get_bounding_vol().calc_cull_result(fr);
  if (cr != cull_result::FRUSTUM_OUTSIDE)
  {
    draw_node(node, fr);
    draw_children(node, fr);
  }
}

void forward_renderer::draw_node(const scene_node& node, const frustum& fr)
{
  node.render();
  m_render_stats.num_nodes_rendered++;
}

void forward_renderer::draw_children(const scene_node& node, const frustum& fr)
{
}

void forward_renderer::draw_blended_nodes(const frustum& fr)
{
}



