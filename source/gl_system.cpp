// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include <string>
#include "gl_system.h"
#include "gl_includes.h"
#include "log.h"

void check_gl_error(const char* statement, const char* filename, int line)
{
  GLenum err = glGetError();
  while (err != GL_NO_ERROR)
  {
    std::string str;
    if (err == GL_INVALID_ENUM) str = "GL_INVALID_ENUM";
    else if (err == GL_INVALID_VALUE) str = "GL_INVALID_VALUE";
    else if (err == GL_INVALID_OPERATION) str = "GL_INVALID_OPERATION";
    else if (err == GL_OUT_OF_MEMORY) str = "GL_OUT_OF_MEMORY";

#ifdef GL_STACK_OVERFLOW
    else if (err == GL_STACK_OVERFLOW) str = "GL_STACK_OVERFLOW";
#endif

#ifdef GL_STACK_UNDERFLOW
    else if (err == GL_STACK_UNDERFLOW) str = "GL_STACK_UNDERFLOW";
#endif

#ifdef GL_INVALID_FRAMEBUFFER_OPERATION
    else if (err == GL_INVALID_FRAMEBUFFER_OPERATION) str = "GL_INVALID_FRAMEBUFFER_OPERATION";
#endif

#ifdef GL_TABLE_TOO_LARGE
    else if (err == GL_TABLE_TOO_LARGE) str = "GL_TABLE_TOO_LARGE";
#endif

    else str = "Unknown error!";

    log(msg() 
      << "OpenGL error: " << str 
      << " for statement " << statement 
      << " file: " << filename 
      << " line: " << line);

    err = glGetError();
  }
}

void log_gl_info()
{
  const GLubyte* renderer = glGetString(GL_RENDERER);
  const GLubyte* version = glGetString(GL_VERSION);

  if (!renderer || !version)
  {
    log("GL context not ready.\n");
    return;
  }

  log(msg() << "Renderer: " << renderer);
  log(msg() << "OpenGL version supported: " << version);

  // From: https://capnramses.github.io//opengl/glcontext2.html

  GLenum params[] = {
    GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,
    GL_MAX_CUBE_MAP_TEXTURE_SIZE,
    GL_MAX_DRAW_BUFFERS,
    GL_MAX_FRAGMENT_UNIFORM_COMPONENTS,
    GL_MAX_TEXTURE_IMAGE_UNITS,
    GL_MAX_TEXTURE_SIZE,
    GL_MAX_VARYING_FLOATS,
    GL_MAX_VERTEX_ATTRIBS,
    GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS,
    GL_MAX_VERTEX_UNIFORM_COMPONENTS,
    GL_MAX_VIEWPORT_DIMS,
    GL_STEREO,
  };
  const char* names[] = {
    "GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS",
    "GL_MAX_CUBE_MAP_TEXTURE_SIZE",
    "GL_MAX_DRAW_BUFFERS",
    "GL_MAX_FRAGMENT_UNIFORM_COMPONENTS",
    "GL_MAX_TEXTURE_IMAGE_UNITS",
    "GL_MAX_TEXTURE_SIZE",
    "GL_MAX_VARYING_FLOATS",
    "GL_MAX_VERTEX_ATTRIBS",
    "GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS",
    "GL_MAX_VERTEX_UNIFORM_COMPONENTS",
    "GL_MAX_VIEWPORT_DIMS",
    "GL_STEREO",
  };

  // integers - only works if the order is 0-10 integer return types
  for (int i = 0; i < 10; i++) {
    int v = 0;
    glGetIntegerv(params[i], &v);
    log(msg() << names[i] << ": " << v);
  }
  // others
  int v[2];
  v[0] = v[1] = 0;
  glGetIntegerv(params[10], v);
  log(msg() << names[10] << ": " << v[0] << ", " << v[1]);
  unsigned char s = 0;
  glGetBooleanv(params[11], &s);
  log(msg() << names[11] << ": " << (unsigned int)s);
}

