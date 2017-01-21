// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

// Build libpng: in libpng, 
//   cp scripts/makefile.darwin .. ; make -f makefile.darwin
// That builds libpng.a in the libpng dir. Then in source/main/
//   make clean ; make ; make run

#include <iostream>
#include <stdio.h>
//#include <unistd.h>

#include "camera.h"
#include "gl_1_1_renderer.h"
#include "gl_2_renderer.h"
#include "gl_includes.h"
#include "gl_shader.h"
#include "gl_system.h"
#include "look_at.h"
#include "projection.h"
#include "gl_1_1_solid_scene_node.h" // TODO TEMP TEST
#include "md3_node.h"
#include "texture.h"
#include "timer.h"

static int WIN_X = 1000;
static int WIN_Y = 500;

gl_1_1_renderer rend_1;
//gl_2_renderer rend_1;
//gl_1_1_renderer rend_2;
gl_2_renderer rend_2;

scene_graph sg_1;
scene_graph sg_2;

void set_up_rend(renderer& rend, bool left_side)
{
  rend.init_on_gl_thread();

  camera left_cam, right_cam;
  float eye_sep = 0.5f;
  float y_dist = 10.f;
  float z_dist = 20.0f;
  vec3 left(-eye_sep, y_dist, z_dist);
  vec3 right(eye_sep, y_dist, z_dist);
  vec3 up(0, 1, 0);
  look_at(left, -left, up).set_matrix(left_cam.look_at_matrix);
  look_at(right, -right, up).set_matrix(right_cam.look_at_matrix);

  perspective p(45, 1, 0.1, 10000);
  p.set_matrix(left_cam.proj_matrix);
  p.set_matrix(right_cam.proj_matrix);

  if (left_side)
  {
    rend.set_view(0, view(viewport(0, 0, WIN_X / 2, WIN_Y), left_cam));
  }
  else
  {
    rend.set_view(0, view(viewport(WIN_X / 2, 0, WIN_X / 2, WIN_Y), right_cam));
  }
}

void set_up_gl_1_1_scene(scene_graph& sg)
{
  auto root = std::make_shared<scene_node>();
  sg.add_node(root);

  // Add MD3 model
  auto md3_root = std::make_shared<md3_node>();
  mat4 scale_down;
  scale_down.scale(.1f, .1f, .1f); // rather large by default
  md3_root->get_xform() = mult(scale_down, mat4().rotate_x_radians(-M_PI_2));
  sg.add_node(md3_root);
  sg.add_connection(root->get_id(), md3_root->get_id());

  auto sphere = std::make_shared<gl_1_1_sphere_scene_node>();
  sphere->get_xform().translate(vec3(-5, 0, -5));
  sg.add_node(sphere);

  auto teapot = std::make_shared<gl_1_1_teapot_scene_node>();
  mat4 m = mult(mat4().scale(.5f, .5f, .5f), mat4().rotate_x_radians(-M_PI_2));
  m = mult(m, mat4().translate(vec3(0, 0, 3.f)));
  teapot->get_xform() = mult(m, mat4().rotate_z_radians(M_PI_2));
  sg.add_node(teapot);

  auto plane = std::make_shared<gl_1_1_plane_scene_node>();
  plane->get_xform().translate(vec3(0, -2.f, 0));
  sg.add_node(plane);

  sg.add_connection(root->get_id(), plane->get_id());
  sg.add_connection(root->get_id(), sphere->get_id());
  sg.add_connection(root->get_id(), teapot->get_id());

  //sg.add_node(child);
  //sg.add_node(gchild);
  //sg.add_connection(root->get_id(), child->get_id());
  //sg.add_connection(child->get_id(), gchild->get_id());
  //sg.add_connection(gchild->get_id(), ggchild->get_id());

  /*
  texture tex;
  tex.set_active_texture_id(2);
  bool b = tex.load("textures/heart.png");
  assert(b);
  tex.upload_on_gl_thread();
  tex.use_on_gl_thread();


  glUseProgram(0); // back to fixed function
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glColor4f(1,1,1,1);
  //  glActiveTexture(GL_TEXTURE0);
  //  glBindTexture(GL_TEXTURE_2D, m_tex[1]);
  //  glEnable(GL_TEXTURE_2D);
  glTranslated(0,0,-1);
  glBegin(GL_QUADS);
  float x1 = 0.5f;
  float x2 = 1.0f;
  float y1 = 0.0f;
  float y2 = 0.5f;
  glTexCoord2d(0,0);glVertex2f(x1, y1);
  glTexCoord2d(1,0);glVertex2f(x2, y1);
  glTexCoord2d(1,1);glVertex2f(x2, y2);
  glTexCoord2d(0,1);glVertex2f(x1, y2);
  glEnd();
  */
}

void render(renderer& rend, scene_graph& sg)
{
  rend.begin_render_on_gl_thread(sg);

  rend.render_on_gl_thread(0);
  
  rend.end_render_on_gl_thread();
}

void display()
{
  //time_this_block("Rendering");

  GL_CHECK(glClearColor(1, 0, 0, 1));
  GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
  GL_CHECK(glEnable(GL_DEPTH_TEST));

  render(rend_1, sg_1);
  render(rend_2, sg_2);


////    rend.destroy_on_gl_thread();
 
///    tex.destroy_on_gl_thread();
 
  glutSwapBuffers();
//    usleep(10000); // to stop my mac melting :(
  glutPostRedisplay();
}

void reshape(int x, int y)
{
  WIN_X = x;
  WIN_Y = y;
    
  glViewport(0, 0, x, y);
}

void mouse(int button, int state, int x, int y)
{
}

void key(unsigned char c, int x, int y)
{
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);

  // https://pleiades.ucsc.edu/hyades/OpenGL_on_OS_X
  glutInitDisplayMode(
      //GLUT_3_2_CORE_PROFILE | 
      GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);

  glutInitWindowSize(WIN_X, WIN_Y);
  glutCreateWindow("Hello"); 

  glewInit();

  // log_gl_info();

  set_up_rend(rend_1, true);
  set_up_rend(rend_2, false);
  set_up_gl_1_1_scene(sg_1);
  set_up_gl_1_1_scene(sg_2);

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMouseFunc(mouse);
  glutKeyboardFunc(key);
  glutMainLoop();
  return 0;
} 
