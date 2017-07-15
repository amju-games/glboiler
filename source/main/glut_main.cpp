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

#include "gl_includes.h"
#include "gl_system.h"
#include "obj_state.h"
#include "md3_state.h"
#include "resource_manager.h"
#include "tweak.h"

#ifdef WIN32
#include <Windows.h>
#endif

static int WIN_X = 800;
static int WIN_Y = 800;

resource_manager rm;

state* the_state = new obj_state; 
//state* the_state = new md3_state;

void onKey(unsigned char ch, int x, int y)
{
  if (ch == 'r')
  {
    rm.reload_all();
  }
}

void display()
{
  //time_this_block("Rendering");

  rm.update_on_gl_thread();

  GL_CHECK(glClearColor(1, 0, 0, 1));
  GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
  GL_CHECK(glEnable(GL_DEPTH_TEST));

  the_state->render_on_gl_thread();

  draw_tweak_bar();
 
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

  resize_tweak_bar(x, y);
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

  // Sets this thread as the GL render thread, so we can check all GL calls 
  //  are on this same thread.
  set_gl_thread();
 
  the_state->set_window_size(WIN_X, WIN_Y);
  the_state->init_on_gl_thread(rm);

  set_up_tweak_bar();

  // In absence of Ant Tweak Bar takeover, get key events to reload resources etc.
  glutKeyboardFunc(onKey);

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMainLoop();
  return 0;
} 
