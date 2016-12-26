// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include <string>

class gl_shader
{
public:
  bool load(const std::string& vert_filename, const std::string& frag_filename);

  bool compile_on_gl_thread();
  void use_on_gl_thread();

  void set_float_on_gl_thread(const std::string& name, float f);
  void set_int_on_gl_thread(const std::string& name, int i);

private:
  unsigned int m_program_id = 0;
  std::string m_vert_shader_source;
  std::string m_frag_shader_source;
};

