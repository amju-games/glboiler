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

#ifdef YES_ANT_TWEAK_BAR
#include <AntTweakBar.h>
#endif

#include "gl_includes.h"
#include "gl_system.h"
#include "md3_state.h"

#ifdef WIN32
#include <Windows.h>
#endif

#ifdef YES_ANT_TWEAK_BAR

// For AntTweakBar exmaple
// This example displays one of the following shapes
typedef enum { SHAPE_TEAPOT = 1, SHAPE_TORUS, SHAPE_CONE } Shape;
#define NUM_SHAPES 3
Shape g_CurrentShape = SHAPE_TORUS;
// Shapes scale
float g_Zoom = 1.0f;
// Shape orientation (stored as a quaternion)
float g_Rotation[] = { 0.0f, 0.0f, 0.0f, 1.0f };
// Auto rotate
int g_AutoRotate = 0;
int g_RotateTime = 0;
float g_RotateStart[] = { 0.0f, 0.0f, 0.0f, 1.0f };
// Shapes material
float g_MatAmbient[] = { 0.5f, 0.0f, 0.0f, 1.0f };
float g_MatDiffuse[] = { 1.0f, 1.0f, 0.0f, 1.0f };
// Light parameter
float g_LightMultiplier = 1.0f;
float g_LightDirection[] = { -0.57735f, -0.57735f, -0.57735f };

// Return elapsed time in milliseconds
int GetTimeMs()
{
#if !defined(_WIN32)
  return glutGet(GLUT_ELAPSED_TIME);
#else
  // glutGet(GLUT_ELAPSED_TIME) seems buggy on Windows
  return (int)GetTickCount();
#endif
}

//  Callback function called when the 'AutoRotate' variable value of the tweak bar has changed
void TW_CALL SetAutoRotateCB(const void *value, void *clientData)
{
  (void)clientData; // unused

  g_AutoRotate = *(const int *)value; // copy value to g_AutoRotate
  if (g_AutoRotate != 0)
  {
    // init rotation
    g_RotateTime = GetTimeMs();
    g_RotateStart[0] = g_Rotation[0];
    g_RotateStart[1] = g_Rotation[1];
    g_RotateStart[2] = g_Rotation[2];
    g_RotateStart[3] = g_Rotation[3];

    // make Rotation variable read-only
    TwDefine(" TweakBar/ObjRotation readonly ");
  }
  else
    // make Rotation variable read-write
    TwDefine(" TweakBar/ObjRotation readwrite ");
}


//  Callback function called by the tweak bar to get the 'AutoRotate' value
void TW_CALL GetAutoRotateCB(void *value, void *clientData)
{
  (void)clientData; // unused
  *(int *)value = g_AutoRotate; // copy g_AutoRotate to value
}
// Ant Tweak bar
#endif // YES_ANT_TWEAK_BAR


static int WIN_X = 800;
static int WIN_Y = 800;

state* the_state = new md3_state;

void display()
{
  //time_this_block("Rendering");

  GL_CHECK(glClearColor(1, 0, 0, 1));
  GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
  GL_CHECK(glEnable(GL_DEPTH_TEST));

  the_state->render_on_gl_thread();

#ifdef YES_ANT_TWEAK_BAR
  // Draw tweak bars
  glViewport(0, 0, WIN_X, WIN_Y);
  TwDraw();
#endif // YES_ANT_TWEAK_BAR

 
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

#ifdef YES_ANT_TWEAK_BAR
  // Send the new window size to AntTweakBar
  TwWindowSize(x, y);
#endif
}

#ifdef YES_ANT_TWEAK_BAR
void set_up_ant_tweak_bar()
{
  // Ant Tweak Bar
  TwBar *bar; // Pointer to the tweak bar
  float axis[] = { 0.7f, 0.7f, 0.0f }; // initial model rotation
  float angle = 0.8f;
  // Initialize AntTweakBar
  TwInit(TW_OPENGL, NULL);
  // Set GLUT event callbacks
  // - Directly redirect GLUT mouse button events to AntTweakBar
  glutMouseFunc((GLUTmousebuttonfun)TwEventMouseButtonGLUT);
  // - Directly redirect GLUT mouse motion events to AntTweakBar
  glutMotionFunc((GLUTmousemotionfun)TwEventMouseMotionGLUT);
  // - Directly redirect GLUT mouse "passive" motion events to AntTweakBar (same as MouseMotion)
  glutPassiveMotionFunc((GLUTmousemotionfun)TwEventMouseMotionGLUT);
  // - Directly redirect GLUT key events to AntTweakBar
  glutKeyboardFunc((GLUTkeyboardfun)TwEventKeyboardGLUT);
  // - Directly redirect GLUT special key events to AntTweakBar
  glutSpecialFunc((GLUTspecialfun)TwEventSpecialGLUT);
  // - Send 'glutGetModifers' function pointer to AntTweakBar;
  //   required because the GLUT key event functions do not report key modifiers states.
  TwGLUTModifiersFunc(glutGetModifiers);

  // Create a tweak bar
  bar = TwNewBar("GL Boiler");
  TwDefine(" GLOBAL help='OpenGL/rendering experiments. Jason Colman 2017' "); // Message added to the help bar.
  //TwDefine(" TweakBar size='200 400' color='96 216 224' "); // change default tweak bar size and color

  // Add 'g_Zoom' to 'bar': this is a modifable (RW) variable of type TW_TYPE_FLOAT. Its key shortcuts are [z] and [Z].
  TwAddVarRW(bar, "Zoom", TW_TYPE_FLOAT, &g_Zoom,
    " min=0.01 max=2.5 step=0.01 keyIncr=z keyDecr=Z help='Scale the object (1=original size).' ");

  // Add 'g_Rotation' to 'bar': this is a variable of type TW_TYPE_QUAT4F which defines the object's orientation
  TwAddVarRW(bar, "ObjRotation", TW_TYPE_QUAT4F, &g_Rotation,
    " label='Object rotation' opened=true help='Change the object orientation.' ");

  // Add callback to toggle auto-rotate mode (callback functions are defined above).
  TwAddVarCB(bar, "AutoRotate", TW_TYPE_BOOL32, SetAutoRotateCB, GetAutoRotateCB, NULL,
    " label='Auto-rotate' key=space help='Toggle auto-rotate mode.' ");

  // Add 'g_LightMultiplier' to 'bar': this is a variable of type TW_TYPE_FLOAT. Its key shortcuts are [+] and [-].
  TwAddVarRW(bar, "Multiplier", TW_TYPE_FLOAT, &g_LightMultiplier,
    " label='Light booster' min=0.1 max=4 step=0.02 keyIncr='+' keyDecr='-' help='Increase/decrease the light power.' ");

  // Add 'g_LightDirection' to 'bar': this is a variable of type TW_TYPE_DIR3F which defines the light direction
  TwAddVarRW(bar, "LightDir", TW_TYPE_DIR3F, &g_LightDirection,
    " label='Light direction' opened=true help='Change the light direction.' ");

  // Add 'g_MatAmbient' to 'bar': this is a variable of type TW_TYPE_COLOR3F (3 floats color, alpha is ignored)
  // and is inserted into a group named 'Material'.
  TwAddVarRW(bar, "Ambient", TW_TYPE_COLOR3F, &g_MatAmbient, " group='Material' ");

  // Add 'g_MatDiffuse' to 'bar': this is a variable of type TW_TYPE_COLOR3F (3 floats color, alpha is ignored)
  // and is inserted into group 'Material'.
  TwAddVarRW(bar, "Diffuse", TW_TYPE_COLOR3F, &g_MatDiffuse, " group='Material' ");

  // Add the enum variable 'g_CurrentShape' to 'bar'
  // (before adding an enum variable, its enum type must be declared to AntTweakBar as follow)
  {
    // ShapeEV associates Shape enum values with labels that will be displayed instead of enum values
    TwEnumVal shapeEV[NUM_SHAPES] = { { SHAPE_TEAPOT, "Teapot" }, { SHAPE_TORUS, "Torus" }, { SHAPE_CONE, "Cone" } };
    // Create a type for the enum shapeEV
    TwType shapeType = TwDefineEnum("ShapeType", shapeEV, NUM_SHAPES);
    // add 'g_CurrentShape' to 'bar': this is a variable of type ShapeType. Its key shortcuts are [<] and [>].
    TwAddVarRW(bar, "Shape", shapeType, &g_CurrentShape, " keyIncr='<' keyDecr='>' help='Change object shape.' ");
  }
}
#endif

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
  glutMainLoop();
  return 0;
} 
