// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include "gl_includes.h"
#include "gl_shader.h"
#include "light.h"
#include "log.h"
#include "look_at.h"
#include "mat3.h"
#include "opaque_pass.h"
#include "projection.h"
#include "renderer.h"
#include "scene_node.h"
#include "shadow_depth_pass.h"

void opaque_pass::init_on_gl_thread(resource_manager& rm)
{
  m_opaque_pass_shader = rm.get_shader("opaque");
}

void opaque_pass::destroy_on_gl_thread()
{
  m_opaque_pass_shader->destroy_on_gl_thread(); // leave this to res manager?
}

void opaque_pass::render_on_gl_thread()
{
  m_opaque_pass_shader->use_on_gl_thread();

  m_opaque_pass_shader->set_int_on_gl_thread("diffuse_map", 0);
  m_opaque_pass_shader->set_int_on_gl_thread("shadow_map", 1);
//  m_opaque_pass_shader->set_int_on_gl_thread("normal_map", 2);
//  m_opaque_pass_shader->set_int_on_gl_thread("specular_map", 3);

  int w, h;
  m_shadow_map->get_size(&w, &h);
  m_opaque_pass_shader->set_int_on_gl_thread("shadow_map_size", w);
  m_opaque_pass_shader->set_mat4_on_gl_thread("light_matrix", m_light_matrix);

  view* v = get_renderer()->get_view();
  const camera& cam = v->get_camera();

  m_opaque_pass_shader->set_mat4_on_gl_thread("look_at_matrix", cam.look_at_matrix);
  m_opaque_pass_shader->set_mat4_on_gl_thread("proj_matrix", cam.proj_matrix);

  frustum frust = v->calc_frustum();

  m_shadow_map->use_texture_on_gl_thread();

  // Render opaque geom
  GL_CHECK(glCullFace(GL_BACK));
  GL_CHECK(glEnable(GL_CULL_FACE));
  GL_CHECK(glEnable(GL_DEPTH_TEST));

  traverse_scene_for_pass(render_pass_type::FORWARD_OPAQUE_PASS, frust);
}

void opaque_pass::draw_node(const scene_node& node, const frustum& fr, const mat4& xform)
{
  // Using m_opaque_pass_shader
  // So setting material sets uniforms on a known shader
  node.use_material_on_gl_thread(); 

  m_opaque_pass_shader->set_mat4_on_gl_thread("world_matrix", xform);
  mat3 norm(xform);
  norm = norm.inverse_transpose();
  m_opaque_pass_shader->set_mat3_on_gl_thread("normal_matrix", norm);

  node.render_on_gl_thread();
}

void opaque_pass::draw_bounding_vol(
  const scene_node& node,
  const frustum& fr,
  const mat4& xform)
{
  // TODO debug material/shader?

  // World xform is identity for bounding volumes, because we want to faithfully draw 
  //  their member values.
  m_opaque_pass_shader->set_mat4_on_gl_thread("world_matrix", mat4());

  std::unique_ptr<bounding_vol> bv(node.get_bounding_vol().transform_by(xform));

  bv->debug_render_on_gl_thread();
}
