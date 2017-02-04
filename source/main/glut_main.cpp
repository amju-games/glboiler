// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

// Build libpng: in libpng, 
//   cp scripts/makefile.darwin .. ; make -f makefile.darwin
// That builds libpng.a in the libpng dir. Then in source/main/
//   make clean ; make ; make run

#include <iostream>
#include <stdio.h>
#ifdef MACOSX
#include <unistd.h>
#endif

#include "camera.h"
#include "gl_1_1_renderer.h"
#include "gl_2_renderer.h"
#include "gl_includes.h"
#include "gl_shader.h"
#include "gl_system.h"
#include "look_at.h"
#include "material.h"
#include "projection.h"
#include "gl_1_1_solid_scene_node.h" // TODO TEMP TEST
#include "md3_node.h"
#include "md3_state.h"
#include "texture.h"
#include "timer.h"

static int WIN_X = 1800;
static int WIN_Y = 800;

state* the_state = new md3_state;

void display()
{
  //time_this_block("Rendering");

  GL_CHECK(glClearColor(1, 0, 0, 1));
  GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
  GL_CHECK(glEnable(GL_DEPTH_TEST));

  the_state->render_on_gl_thread();

 
  glutSwapBuffers();

#ifdef MACOSX
  usleep(10000); // to stop my mac melting :(
#endif

  glutPostRedisplay();

  float dt = 0.01f;
  the_state->update(dt);
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

#ifdef WIN32
  glewInit();
#endif

  // log_gl_info();

  the_state->set_window_size(WIN_X, WIN_Y);
  resource_manager rm;
  the_state->init_on_gl_thread(rm);

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMouseFunc(mouse);
  glutKeyboardFunc(key);
  glutMainLoop();
  return 0;
} 
