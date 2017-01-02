// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

#include "forward_renderer.h"
#include "gl_includes.h"
#include "gl_shader.h"
#include "look_at.h"
#include "projection.h"

const int shadow_map_size = 16;

void forward_renderer::init_on_gl_thread()
{
  m_shadow_map.set_render_flags(render_to_texture::RENDER_DEPTH);
  m_shadow_map.set_size(shadow_map_size, shadow_map_size); 
  m_shadow_map.init_on_gl_thread(); 

  // Render shadow map, used for both eyes
  m_depth_shader.load("shaders/test_v.txt", "shaders/test_f.txt");
  m_depth_shader.compile_on_gl_thread();
  m_depth_shader.use_on_gl_thread();
}

void forward_renderer::render_on_gl_thread(const scene_description& sd)
{
  clear_blended_nodes();

  glEnable(GL_CULL_FACE);

  shadow_map_pass(sd);

  gl_shader sh;
  sh.load("shaders/test_v.txt", "shaders/test_f.txt");
  sh.compile_on_gl_thread();
  sh.use_on_gl_thread();
  sh.set_int_on_gl_thread("shadow_map", 0);
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
}

void forward_renderer::clear_blended_nodes()
{
  m_blended_nodes.clear();
}

void forward_renderer::shadow_map_pass(const scene_description& sd)
{
  // Set light dir/frustum
  mat4 proj;
  perspective p(45, 1, 1, 10);
  p.set_matrix(proj);
  m_depth_shader.set_mat4_on_gl_thread("proj_matrix", proj);

  vec3 light_pos(0, 2, 3);
  camera light_cam;
  look_at(light_pos, -light_pos, vec3(0, 1, 0)).set_matrix(light_cam.look_at_matrix
);
  view light_view(viewport(0, 0, shadow_map_size, shadow_map_size), light_cam);
  light_view.set_gl_viewport();

  // Rotate the light
  static float a = 0;
  a += 0.05f;
  mat4 rot;
  load_identity(rot);
  rotate_y_radians(rot, a);

  mat4 modl;
  mult(rot, light_cam.look_at_matrix, modl);
  m_depth_shader.set_mat4_on_gl_thread("look_at_matrix",
    light_cam.look_at_matrix);

  // Mult projection and modelview matrices: this is the light matrix, which
  //  we use in the second pass. Bias transforms (-1, 1) to (0, 1) space.
  const mat4 bias =
  {
    0.5, 0.0, 0.0, 0.0,
    0.0, 0.5, 0.0, 0.0,
    0.0, 0.0, 0.5, 0.0,
    0.5, 0.5, 0.5, 1.0
  };
  mat4 m;
  mult(modl, proj, m);
  mult(m, bias, m_light_matrix);

  m_shadow_map.begin_on_gl_thread();

  // Get light frustum (for each light which casts shadows?!)
  frustum light_frustum;

  GL_CHECK(glCullFace(GL_FRONT));

  const scene_node& node = sd.get_root_node();
  cull_result cr = node.get_bounding_vol().calc_cull_result(light_frustum);
  if (cr != cull_result::FRUSTUM_OUTSIDE)
  {
    draw_node(node, light_frustum, &m_depth_shader);
    draw_children(node, light_frustum);
  }

  m_shadow_map.end_on_gl_thread();
}

void forward_renderer::opaque_pass(const scene_description& sd, const frustum& fr, gl_shader* override_shader)
{
  GL_CHECK(glCullFace(GL_BACK));

  const scene_node& node = sd.get_root_node();
  cull_result cr = node.get_bounding_vol().calc_cull_result(fr);
  if (cr != cull_result::FRUSTUM_OUTSIDE)
  {
    draw_node(node, fr, override_shader);
    draw_children(node, fr);
  }
}

void forward_renderer::draw_node(const scene_node& node, const frustum& fr, gl_shader* override_shader)
{
/*
  if (override_shader)
  {
    override_shader->use_this_shader();
  }
  else
  {
    node.use_material();
  }
*/
  node.render();
  m_render_stats.num_nodes_rendered++;
}

void forward_renderer::draw_children(const scene_node& node, const frustum& fr, gl_shader* override_shader)
{
}

void forward_renderer::draw_blended_nodes(const frustum& fr)
{
}



