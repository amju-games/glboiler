// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include "obj_state.h"
#include "obj_scene_node.h"
#include "gl_1_1_solid_scene_node.h"
#include "gl_2_renderer.h"

void obj_state::init_on_gl_thread(resource_manager& rm)
{
  // Add shader resources
  std::shared_ptr<gl_shader> opaque(new gl_shader);
  opaque->load("shaders/opaque.v.txt", "shaders/opaque.f.txt");
  rm.add_gl_resource("opaque", opaque);

  std::shared_ptr<gl_shader> shadow_depth_opaque(new gl_shader);
  shadow_depth_opaque->load("shaders/shadow_depth_opaque.v.txt", "shaders/shadow_depth_opaque.f.txt");
  rm.add_gl_resource("shadow_depth_opaque", shadow_depth_opaque);

  // Add mesh resources

  // Add texture resources? No need, if we load on demand.
  // Same for other resources then..? 

  state::init_on_gl_thread(rm);
}

void obj_state::set_up_scene_graph_on_gl_thread(resource_manager& rm)
{
  m_sg.reset(new scene_graph);

  auto root = std::make_shared<scene_node>();
  m_sg->add_node(root);

  std::shared_ptr<material> mat_white(new material);
  mat_white->set_textures({ "textures/test_card.png" }, rm);

  auto obj = std::make_shared<obj_scene_node>();

  obj->load("obj/cube_0.5.obj");
//  obj->load("obj/reduced_head_3b.obj");
//  obj->load("obj/ball.obj");

  mat4 scale_down;
  scale_down.scale(.1f, .1f, .1f); // rather large by default
  obj->get_xform() = scale_down;

  m_sg->add_node(obj);
  obj->set_material(mat_white);

  m_sg->add_connection(root->get_id(), obj->get_id());
}

void obj_state::create_renderer_on_gl_thread(resource_manager& rm)
{
  m_renderer.reset(new gl_2_renderer);
  set_up_renderer_on_gl_thread(*m_renderer, 0, 0, m_window_w, m_window_h, rm);
}

