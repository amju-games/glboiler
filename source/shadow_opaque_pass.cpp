// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include "gl_includes.h"
#include "gl_shader.h"
#include "light.h"
#include "log.h"
#include "look_at.h"
#include "projection.h"
#include "renderer.h"
#include "scene_node.h"
#include "shadow_depth_pass.h"
#include "shadow_opaque_pass.h"

void shadow_opaque_pass::init_on_gl_thread()
{
  m_opaque_pass_shader.load("shaders/gl_2_replicate_fixed_v.txt", "shaders/gl_2_replicate_fixed_f.txt");
  m_opaque_pass_shader.upload_on_gl_thread();
}

void shadow_opaque_pass::destroy_on_gl_thread()
{
  m_opaque_pass_shader.destroy_on_gl_thread();
}

void shadow_opaque_pass::render_on_gl_thread()
{
  m_opaque_pass_shader.use_on_gl_thread();

  m_opaque_pass_shader.set_int_on_gl_thread("diffuse_map", 0);
  m_opaque_pass_shader.set_int_on_gl_thread("shadow_map", 1);

  //  sh.set_int_on_gl_thread("shadow_map_size", m_shadow_map_size);
  m_opaque_pass_shader.set_mat4_on_gl_thread("light_matrix", m_light_matrix);

  view* v = get_renderer()->get_view();
  const camera& cam = v->get_camera();

  m_opaque_pass_shader.set_mat4_on_gl_thread("look_at_matrix", cam.look_at_matrix);
  m_opaque_pass_shader.set_mat4_on_gl_thread("proj_matrix", cam.proj_matrix);

  frustum frust = v->calc_frustum();

  m_shadow_map->use_texture_on_gl_thread();

  // Render opaque geom
  GL_CHECK(glCullFace(GL_BACK));
  GL_CHECK(glEnable(GL_CULL_FACE));
  GL_CHECK(glEnable(GL_DEPTH_TEST));

  traverse_scene_for_pass(render_pass_type::FORWARD_OPAQUE_PASS, frust);
}

void shadow_opaque_pass::draw_node(const scene_node& node, const frustum& fr, const mat4& xform)
{
  // Using m_opaque_pass_shader
  // So setting material sets uniforms on a known shader
  node.use_material_on_gl_thread(); 

  m_opaque_pass_shader.set_mat4_on_gl_thread("world_matrix", xform);
  node.render_on_gl_thread();
}
