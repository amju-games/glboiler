// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <assert.h>
#include "gl_includes.h"
#include "gl_shader.h"
#include "log.h"

void gl_shader::set_mat4_on_gl_thread(const std::string& name, const mat4 m)
{
  GL_CHECK(GLint loc = glGetUniformLocation(m_program_id, name.c_str()));
  if (loc == -1)
  {
    return;
  }

  GL_CHECK(glUniformMatrix4fv(loc, 1, false, m));
}

void gl_shader::set_float_on_gl_thread(const std::string& name, float f)
{
  GL_CHECK(GLint loc = glGetUniformLocation(m_program_id, name.c_str()));
  if (loc == -1)
  {
    return;
  }

  GL_CHECK(glUniform1f(loc, f));
}

void gl_shader::set_int_on_gl_thread(const std::string& name, int i)
{
  GL_CHECK(GLint loc = glGetUniformLocation(m_program_id, name.c_str()));
  if (loc == -1)
  {
    return;
  }

  GL_CHECK(glUniform1i(loc, i));
}

static bool read_file(const std::string& filename, std::string* result)
{
  std::ifstream f;
  f.open(filename);
  if (!f.is_open())
  {
    std::cout << "Failed to open file " << filename << "\n";
    return false;
  }

  while (!f.eof())
  {
    std::string str;
    std::getline(f, str);
    (*result) += str + "\r\n";
  }

  return true;
}

bool gl_shader::load(const std::string& vertFilename, const std::string& fragFilename)
{
  if (!read_file(vertFilename, &m_vert_shader_source))
  {
    std::cout << "Failed to read vertex shader from file\n";
    return false;
  }

  if (!read_file(fragFilename, &m_frag_shader_source))
  {
    std::cout << "Failed to read fragment shader from file\n";
    return false;
  }
 
  return true;
}

bool gl_shader::compile_on_gl_thread()
{
  GL_CHECK(GLuint vertSh = glCreateShader(GL_VERTEX_SHADER));
  GL_CHECK(GLuint fragSh = glCreateShader(GL_FRAGMENT_SHADER));

  const char* vert_source_cstr = m_vert_shader_source.c_str();
  const char* frag_source_cstr = m_frag_shader_source.c_str();
  GL_CHECK(glShaderSource(vertSh, 1, &vert_source_cstr, nullptr));
  GL_CHECK(glShaderSource(fragSh, 1, &frag_source_cstr, nullptr));

  GLint compiled = 0;
  static const int ERROR_BUF_SIZE = 2000;
  GLcharARB buf[ERROR_BUF_SIZE]; // error string buffer

  GL_CHECK(glCompileShader(vertSh));

  GL_CHECK(glGetShaderiv(vertSh, GL_COMPILE_STATUS, &compiled));
  if (!compiled)
  {
    GL_CHECK(glGetShaderInfoLog(vertSh, ERROR_BUF_SIZE, 0, buf));
    log(buf);
    return false;
  }

  GL_CHECK(glCompileShader(fragSh));
  
  GL_CHECK(glGetShaderiv(fragSh, GL_COMPILE_STATUS, &compiled));
  if (!compiled)
  {
    GL_CHECK(glGetShaderInfoLog(fragSh, ERROR_BUF_SIZE, 0, buf));
    log(buf);
    return false;
  }

  m_program_id = glCreateProgram();
  GL_CHECK(glAttachShader(m_program_id, vertSh));
  GL_CHECK(glAttachShader(m_program_id, fragSh));
  GL_CHECK(glLinkProgram(m_program_id));
  GLint linked;
  GL_CHECK(glGetProgramiv(m_program_id, GL_OBJECT_LINK_STATUS_ARB, &linked));
  if (!linked)
  {
    GL_CHECK(glGetProgramInfoLog(m_program_id, ERROR_BUF_SIZE, 0, buf));
    log(buf);
    return false;
  }

  use_on_gl_thread(); // bind shader so we can set uniforms

  return true;
}

void gl_shader::use_on_gl_thread()
{
  GL_CHECK(glUseProgram(m_program_id));
}

