// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include "gl_1_1_solid_scene_node.h"
#include "gl_2_renderer.h"
#include "mesh_scene_node.h"
#include "obj_state.h"

void obj_state::init_on_gl_thread(resource_manager& rm)
{
  state::init_on_gl_thread(rm);
}

void obj_state::update(float dt)
{
  mat4 rotate;
  static float f = 0;
  f += dt;
  rotate.rotate_y_radians(f);
  m_root->get_xform() = rotate;
}

void obj_state::set_up_scene_graph_on_gl_thread(resource_manager& rm)
{
  m_sg.reset(new scene_graph);

  auto root = std::make_shared<scene_node>();
  root->add_render_pass(render_pass_type::ALL);

  m_sg->add_node(root);
  m_root = root.get();

  std::shared_ptr<material> mat_white(new material);
  mat_white->set_texture(rm.get_texture("textures/test_card.png"));

  auto obj = std::make_shared<scene_node>();
  m_sg->add_node(obj);
  m_sg->add_connection(root->get_id(), obj->get_id());

  obj->add_render_pass(render_pass_type::SHADOW_PASS | render_pass_type::FORWARD_OPAQUE_PASS);

  // Get obj file resource. Loaded if not already resident.
  // Stores the meshes (groups) in the resource manager when loading.
  std::shared_ptr<gl_mesh> mesh = rm.get_mesh("obj/head_4.obj");

  // Obj file can have multiple meshes (groups). We want each group in a separate node, for
  //  sorting etc. This function makes a scene node for each group, getting the group from
  //  the resource manager.
  std::vector<std::shared_ptr<scene_node>> nodes = mesh->make_scene_nodes(rm);

  // Add each new node to the scene graph, setting render pass flags and connecting
  //  the root node to each sub node.
  for (auto n : nodes)
  {
    n->add_render_pass(render_pass_type::SHADOW_PASS | render_pass_type::FORWARD_OPAQUE_PASS);

    m_sg->add_node(n);
    m_sg->add_connection(obj->get_id(), n->get_id());
  }

//  obj->set_mesh(rm.get_mesh("obj/cube_0.5.obj"));

//  obj->load("obj/reduced_head_3b.obj");
//  obj->load("obj/ball.obj");

  mat4 scale_down;
  scale_down.scale(.1f, .1f, .1f); // rather large by default
  obj->get_xform() = scale_down;
}

void obj_state::create_renderer_on_gl_thread(resource_manager& rm)
{
  m_renderer.reset(new gl_2_renderer);
  set_up_renderer_on_gl_thread(*m_renderer, 0, 0, m_window_w, m_window_h, rm);
}

