// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include "material.h"

void material::set_textures(const strings& texture_names, resource_manager& rm)
{
  for (const std::string& tex_name : texture_names)
  {
    m_textures.push_back(rm.get_texture(tex_name));
  }
}

void material::set_shader(std::shared_ptr<gl_shader> shader)
{
  m_shader = shader;
}

void material::use_on_gl_thread()
{
  if (m_shader)
  {
    m_shader->use_on_gl_thread();
  }

  for (auto tex : m_textures)
  {
    tex->use_on_gl_thread();
  }
}

