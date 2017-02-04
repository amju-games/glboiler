// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

void md3_state::on_enter()
{
  m_sg.reset(new scene_graph);

  auto root = std::make_shared<scene_node>();
  m_sg->add_node(root);

  // Add MD3 model
  auto md3_root = std::make_shared<md3_node>();
  mat4 scale_down;
  scale_down.scale(.1f, .1f, .1f); // rather large by default
  md3_root->get_xform() = mult(scale_down, mat4().rotate_x_radians(-M_PI_2));
  m_sg->sg.add_node(md3_root);
  m_sg->sg.add_connection(root->get_id(), md3_root->get_id());

  static resource_manager rm; // TODO TEMP TEST

  std::shared_ptr<material> mat_test_card(new material);
  std::shared_ptr<material> mat_white(new material);

  mat_test_card->set_textures({ "textures/test_card.png" }, rm);
  mat_white->set_textures({ "textures/white.png" }, rm);

  auto sphere = std::make_shared<gl_1_1_sphere_scene_node>();
  sphere->get_xform().translate(vec3(-5, 0, -5));
  m_sg->sg.add_node(sphere);

  auto teapot = std::make_shared<gl_1_1_teapot_scene_node>();
  mat4 m = mult(mat4().scale(.5f, .5f, .5f), mat4().rotate_x_radians(-M_PI_2));
  m = mult(m, mat4().translate(vec3(0, 0, 3.f)));
  teapot->get_xform() = m;
  teapot->set_material(mat_white);
  m_sg->sg.add_node(teapot);

  auto plane = std::make_shared<gl_1_1_plane_scene_node>();
  plane->get_xform().translate(vec3(0, -2.f, 0));
  m_sg->sg.add_node(plane);

  plane->set_material(mat_test_card);

  m_sg->sg.add_connection(root->get_id(), plane->get_id());
  m_sg->sg.add_connection(root->get_id(), sphere->get_id());
  m_sg->sg.add_connection(root->get_id(), teapot->get_id());
}
 
void md3_state::on_exit()
{
  m_sg.reset(nullptr);
}

void md3_state::render() const
{
}

void md3_state::update(float dt) 
{
  m_sg->update(dt);
}

