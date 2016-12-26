// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <assert.h>
#include "gl_includes.h"
#include "gl_shader.h"

// TODO Make this a program-wide helper
void ReportError(const char* buf)
{
  std::cout << buf << "\n";
}

void gl_shader::set_float_on_gl_thread(const std::string& name, float f)
{
  GLint loc = glGetUniformLocation(m_program_id, name.c_str());
  if (loc == -1)
  {
    return;
  }

  glUniform1f(loc, f);
}

void gl_shader::set_int_on_gl_thread(const std::string& name, int i)
{
  GLint loc = glGetUniformLocation(m_program_id, name.c_str());
  if (loc == -1)
  {
    return;
  }

  glUniform1f(loc, i);
}

static bool ReadFile(const std::string& filename, std::string* result)
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
  if (!ReadFile(vertFilename, &m_vert_shader_source))
  {
    std::cout << "Failed to read vertex shader from file\n";
    return false;
  }

  if (!ReadFile(fragFilename, &m_frag_shader_source))
  {
    std::cout << "Failed to read fragment shader from file\n";
    return false;
  }
 
  return true;
}

bool gl_shader::compile_on_gl_thread()
{
  GLuint vertSh = glCreateShader(GL_VERTEX_SHADER);
  GLuint fragSh = glCreateShader(GL_FRAGMENT_SHADER);

  const char* vert_source_cstr = m_vert_shader_source.c_str();
  const char* frag_source_cstr = m_frag_shader_source.c_str();
  glShaderSource(vertSh, 1, &vert_source_cstr, nullptr);
  glShaderSource(fragSh, 1, &frag_source_cstr, nullptr);

  GLint compiled = 0;
  static const int ERROR_BUF_SIZE = 2000;
  GLcharARB buf[ERROR_BUF_SIZE]; // error string buffer

  glCompileShader(vertSh);

  glGetShaderiv(vertSh, GL_COMPILE_STATUS, &compiled);
  if (!compiled)
  {
    glGetShaderInfoLog(vertSh, ERROR_BUF_SIZE, 0, buf);
    ReportError(buf);
    return false;
  }

  glCompileShader(fragSh);
  
  glGetShaderiv(fragSh, GL_COMPILE_STATUS, &compiled);
  if (!compiled)
  {
    glGetShaderInfoLog(fragSh, ERROR_BUF_SIZE, 0, buf);
    ReportError(buf);
    return false;
  }

  m_program_id = glCreateProgram();
  glAttachShader(m_program_id, vertSh);
  glAttachShader(m_program_id, fragSh);
  glLinkProgram(m_program_id);
  GLint linked;
  glGetProgramiv(m_program_id, GL_OBJECT_LINK_STATUS_ARB, &linked);
  if (!linked)
  {
    glGetProgramInfoLog(m_program_id, ERROR_BUF_SIZE, 0, buf);
    ReportError(buf);
    return false;
  }

  use_on_gl_thread(); // bind shader so we can set uniforms

  return true;
}

void gl_shader::use_on_gl_thread()
{
  glUseProgram(m_program_id);
}

