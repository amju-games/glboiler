// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include "look_at.h"
#include "md3_state.h"
#include "md3_node.h"
#include "gl_1_1_solid_scene_node.h"
#include "gl_2_renderer.h"
#include "gl_1_1_renderer.h"
#include "projection.h"

void md3_state::init_on_gl_thread(resource_manager& rm)
{
  state::init_on_gl_thread(rm);
}

void md3_state::set_up_scene_graph_on_gl_thread(resource_manager& rm)
{
  m_sg.reset(new scene_graph);

  auto root = std::make_shared<scene_node>();
  m_sg->add_node(root);
  root->add_render_pass(render_pass_type::ALL);

  // Add MD3 model
  auto md3_root = std::make_shared<md3_node>();
  md3_root->load(rm);
  md3_root->add_render_pass(render_pass_type::SHADOW_PASS);
  md3_root->add_render_pass(render_pass_type::FORWARD_OPAQUE_PASS);

  mat4 scale_down;
  scale_down.scale(.1f, .1f, .1f); // rather large by default
  md3_root->get_xform() = mult(scale_down, mat4().rotate_x_radians(static_cast<float>(-M_PI_2)));
  m_sg->add_node(md3_root);
  m_sg->add_connection(root->get_id(), md3_root->get_id());

  std::shared_ptr<material> mat_test_card(new material);
  std::shared_ptr<material> mat_white(new material);

  mat_test_card->set_texture(rm.get_texture("textures/test_card.png"));
  mat_white->set_texture(rm.get_texture("textures/white.png"));

  auto sphere = std::make_shared<gl_1_1_sphere_scene_node>();
  sphere->get_xform().translate(vec3(-5, 0, -5));
  sphere->set_material(mat_white);
  m_sg->add_node(sphere);
  sphere->add_render_pass(render_pass_type::SHADOW_PASS);
  sphere->add_render_pass(render_pass_type::FORWARD_OPAQUE_PASS);

  auto teapot = std::make_shared<gl_1_1_teapot_scene_node>();
  mat4 m = mult(mat4().scale(.5f, .5f, .5f), mat4().rotate_x_radians(static_cast<float>(-M_PI_2)));
  m = mult(m, mat4().translate(vec3(0, 0, 3.f)));
  teapot->get_xform() = m;
  teapot->set_material(mat_white);
  m_sg->add_node(teapot);
  teapot->add_render_pass(render_pass_type::SHADOW_PASS);
  teapot->add_render_pass(render_pass_type::FORWARD_OPAQUE_PASS);

  auto plane = std::make_shared<gl_1_1_plane_scene_node>();
  plane->get_xform().translate(vec3(0, -2.f, 0));
  m_sg->add_node(plane);
  plane->add_render_pass(render_pass_type::SHADOW_PASS);
  plane->add_render_pass(render_pass_type::FORWARD_OPAQUE_PASS);

  plane->set_material(mat_test_card);

  m_sg->add_connection(root->get_id(), plane->get_id());
  m_sg->add_connection(root->get_id(), sphere->get_id());
  m_sg->add_connection(root->get_id(), teapot->get_id());
}

void md3_state::create_renderer_on_gl_thread(resource_manager& rm)
{
  m_renderer.reset(new gl_2_renderer);
  
  m_renderer->init_on_gl_thread(rm);

  vec3 eye_pos(0, 10, 30); 

  vec3 look = -normalise(eye_pos);
  const vec3 up(0, 1, 0);
  perspective p(45.0f, 1.0f, 0.1f, 10000.0f);
  camera cam;
  p.set_matrix(cam.proj_matrix);
  look_at(eye_pos, look, up).set_matrix(cam.look_at_matrix);
  m_renderer->set_view(view(viewport(0, 0, m_window_w, m_window_h), cam));
}

