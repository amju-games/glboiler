// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include "md3_state.h"
#include "md3_node.h"
#include "gl_1_1_solid_scene_node.h"
#include "gl_2_renderer.h"
#include "gl_1_1_renderer.h"

void md3_state::init_on_gl_thread(resource_manager& rm)
{
  // Add resources
  std::shared_ptr<gl_shader> opaque(new gl_shader);
  opaque->load("shaders/opaque.v.txt", "shaders/opaque.f.txt");
  rm.add_gl_resource("opaque", opaque);

  std::shared_ptr<gl_shader> shadow_depth_opaque(new gl_shader);
  shadow_depth_opaque->load("shaders/shadow_depth_opaque.v.txt", "shaders/shadow_depth_opaque.f.txt");
  rm.add_gl_resource("shadow_depth_opaque", shadow_depth_opaque);

  //{
  //  std::shared_ptr<texture> tex(new texture);
  //  tex->load("md3/dragon/deranged_crowley.png");
  //  rm.add_gl_resource(tex->get_name(), tex);
  //}
  //{
  //  std::shared_ptr<texture> tex(new texture);
  //  tex->load("md3/dragon/deranged_sir_bruin.png");
  //  rm.add_gl_resource(tex->get_name(), tex);
  //}

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
  set_up_renderer_on_gl_thread(*m_renderer, 0, 0, m_window_w, m_window_h, rm);
}

