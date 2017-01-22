// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include <string>
#include "mat4.h"
#include "resource.h"

class gl_shader : public gl_resource
{
public:
  ~gl_shader();

  bool load(const std::string& vert_filename, const std::string& frag_filename);

  virtual void upload_on_gl_thread() override;
  virtual void use_on_gl_thread() override;
  virtual void destroy_on_gl_thread() override;

  void set_float_on_gl_thread(const std::string& name, float f);
  void set_int_on_gl_thread(const std::string& name, int i);
  void set_mat4_on_gl_thread(const std::string& name, const mat4& m);

private:
  unsigned int m_program_id = 0;
  std::string m_vert_shader_filename;
  std::string m_frag_shader_filename;
  std::string m_vert_shader_source;
  std::string m_frag_shader_source;
  bool m_compiled_ok = false;
  bool m_destroy_called = false;
};

