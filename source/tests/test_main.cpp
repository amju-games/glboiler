// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

// Unit tests 
// To build on Mac:
// First build gtest.a in googletest (only needs doing once):
//   cd source/thirdparty/googletest/make
//   make gtest.a
// Then back in source/tests
//   make  

#include "gl_includes.h"
#include <gtest/gtest.h>

int main(int argc, char * argv[])
{
  ::testing::InitGoogleTest(&argc, argv);

  // Set up GL context so we can do tests involving OpenGL
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(100, 100);
  glutCreateWindow("Hello tests");

  return RUN_ALL_TESTS();
}


