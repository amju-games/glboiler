// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include <stack>
#include "forward_renderer.h"
#include "gl_includes.h"
#include "gl_shader.h"
#include "light.h"
#include "log.h"
#include "look_at.h"
#include "projection.h"

// Bias transforms (-1, 1) to (0, 1) space.
static const mat4 BIAS_MATRIX =
{
  0.5, 0.0, 0.0, 0.0,
  0.0, 0.5, 0.0, 0.0,
  0.0, 0.0, 0.5, 0.0,
  0.5, 0.5, 0.5, 1.0
};

struct traversal_node
{
  traversal_node() = default;
  traversal_node(int id_) : id(id_) {}
  traversal_node(int id_, const mat4& m) : id(id_), combined_matrix(m) {}

  int id = -1;
  mat4 combined_matrix;
};

void forward_renderer::traverse(
  const scene_graph& sg, 
  const frustum& fr, 
  gl_shader* override_shader)
{
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

forward_renderer::forward_renderer()
{
  m_shadow_map_size = 1024;
}

void forward_renderer::destroy_on_gl_thread()
{
  m_depth_shader.destroy_on_gl_thread();
  m_shadow_map.destroy_on_gl_thread();
}

void forward_renderer::init_on_gl_thread()
{
  m_shadow_map.set_render_flags(render_to_texture::RENDER_DEPTH);
  m_shadow_map.set_size(m_shadow_map_size, m_shadow_map_size); 
  m_shadow_map.init_on_gl_thread(); 

  // shader for shadow map
  m_depth_shader.load("shaders/just_depth_v.txt", "shaders/just_depth_f.txt");
  m_depth_shader.compile_on_gl_thread();
  m_depth_shader.use_on_gl_thread();
}

void forward_renderer::render_on_gl_thread(const scene_graph& sd)
{
  clear_blended_nodes();

  glEnable(GL_CULL_FACE);

  shadow_map_pass(sd);

  gl_shader sh;
  sh.load("shaders/test_v.txt", "shaders/test_f.txt");
  sh.compile_on_gl_thread();
  sh.use_on_gl_thread();
  sh.set_int_on_gl_thread("shadow_map", 0);
  sh.set_int_on_gl_thread("shadow_map_size", m_shadow_map_size);
  sh.set_mat4_on_gl_thread("light_matrix", m_light_matrix);

  for (int eye = 0; eye < 2 ; eye++)
  {
    view& this_view = m_view[eye];
    this_view.set_gl_viewport();
    const camera& cam = this_view.get_camera();

    sh.set_mat4_on_gl_thread("look_at_matrix", cam.look_at_matrix);
    sh.set_mat4_on_gl_thread("proj_matrix", cam.proj_matrix);

    frustum frust = this_view.calc_frustum();
  
    m_shadow_map.use_texture_on_gl_thread();

    // Render opaque geom, for each eye
    opaque_pass(sd, frust, &sh);

    // Render blended nodes, for each eye
    draw_blended_nodes(frust);
  }

  m_shadow_map.use_texture_on_gl_thread();
  m_shadow_map.debug_draw_on_gl_thread();

  sh.destroy_on_gl_thread();
}

void forward_renderer::clear_blended_nodes()
{
  m_blended_nodes.clear();
}

void forward_renderer::shadow_map_pass(const scene_graph& sg)
{
  m_depth_shader.use_on_gl_thread();

  // Orbiting light
  static float a = 0;
  a += 0.05f;
  vec3 light_pos(3.0f * cos(a), 2, 3.0f * sin(a));
  directional_light light(light_pos, -light_pos);
  light.calc_matrix(8.0, 1.0, 10.0);
  const mat4& m = light.get_matrix();
  
  m_depth_shader.set_mat4_on_gl_thread("view_proj_matrix", m);

  // Transform with bias and store for second pass
  m_light_matrix = mult(m, BIAS_MATRIX);

  m_shadow_map.begin_on_gl_thread();

  // Get light frustum (for each light which casts shadows?!)
  frustum light_frustum;

  GL_CHECK(glCullFace(GL_FRONT));

  traverse(sg, light_frustum, &m_depth_shader);

  m_shadow_map.end_on_gl_thread();
}

void forward_renderer::opaque_pass(const scene_graph& sg, const frustum& fr, gl_shader* override_shader)
{
  GL_CHECK(glCullFace(GL_BACK));
  traverse(sg, fr, override_shader);
}

void forward_renderer::draw_node(const scene_node& node, const frustum& fr, gl_shader* override_shader, const mat4& xform)
{
  gl_shader* sh = override_shader;

/* TODO use override shader if set, otherwise use material/shader for node
  if (override_shader)
  {
    override_shader->use_this_shader();
  }
  else
  {
    node.use_material();
  }
*/

  sh->set_mat4_on_gl_thread("world_matrix", xform);
  node.render();
  m_render_stats.num_nodes_rendered++;
}

void forward_renderer::draw_blended_nodes(const frustum& fr)
{
}



