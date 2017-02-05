// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include "frustum.h"
#include "gl_includes.h"
#include "gl_shader.h"
#include "light.h"
#include "log.h"
#include "look_at.h"
#include "projection.h"
#include "renderer.h"
#include "shadow_depth_pass.h"

// Bias transforms (-1, 1) to (0, 1) space.
static const mat4 BIAS_MATRIX =
{
  0.5, 0.0, 0.0, 0.0,
  0.0, 0.5, 0.0, 0.0,  0.0, 0.0, 0.5, 0.0,
  0.5, 0.5, 0.5, 1.0
};

void shadow_depth_pass::init_on_gl_thread()
{
  m_shadow_map_size = 1024;

  m_shadow_map.set_render_flags(render_to_texture::RENDER_DEPTH);
  m_shadow_map.set_size(m_shadow_map_size, m_shadow_map_size);
  m_shadow_map.init_on_gl_thread();

  // shader for shadow map
  m_depth_shader.load("shaders/gl_2_just_depth_v.txt", "shaders/gl_2_just_depth_f.txt");
  m_depth_shader.upload_on_gl_thread();
  m_depth_shader.use_on_gl_thread();
}

void shadow_depth_pass::destroy_on_gl_thread()
{
  m_depth_shader.destroy_on_gl_thread();
  m_shadow_map.destroy_on_gl_thread();
}

void shadow_depth_pass::render_on_gl_thread()
{
  GL_CHECK(glFrontFace(GL_CW)); // Not great that we need this here
  GL_CHECK(glEnable(GL_DEPTH_TEST));
  GL_CHECK(glEnable(GL_CULL_FACE)); 

  m_depth_shader.use_on_gl_thread();

  // TODO TEMP TEST
  // Orbiting light
  static float a = 0;
  a += 0.005f;
  float xz = 80.f;
  float y = 20.f;
  vec3 light_pos(xz * cos(a), y, xz * sin(a));
  directional_light light(light_pos, -light_pos);
  light.calc_matrix(20.0, 0.1, 100.0);
  const mat4& m = light.get_matrix();

  m_depth_shader.set_mat4_on_gl_thread("view_proj_matrix", m);

  // Transform with bias and store for second pass
  m_light_matrix = mult(m, BIAS_MATRIX);

  m_shadow_map.begin_on_gl_thread();

  // Get light frustum (for each light which casts shadows?!)
  frustum light_frustum;

  GL_CHECK(glCullFace(GL_FRONT));

  traverse_scene_for_pass(
    render_pass_type::SHADOW_PASS, light_frustum);

  m_shadow_map.end_on_gl_thread();
}

void shadow_depth_pass::draw_node(const scene_node& node, const frustum& fr, const mat4& xform)
{
  // Using m_depth_shader
  m_depth_shader.set_mat4_on_gl_thread("world_matrix", xform);
  node.render_on_gl_thread();
}

