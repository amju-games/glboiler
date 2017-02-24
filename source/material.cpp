// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include "material.h"

material::material()
{
  const int MAX_NUM_TEXTURES = 8;
  m_textures.resize(MAX_NUM_TEXTURES);
}

void material::set_texture(std::shared_ptr<gl_texture> tex, int active_texture_id)
{
  m_textures[active_texture_id] = tex;
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

  int num_textures = static_cast<int>(m_textures.size());
  for (int i = 0; i < num_textures; i++)
  {
    auto tex = m_textures[i];
    if (tex)
    {
      tex->use_on_gl_thread(i);
    }
  }
}

