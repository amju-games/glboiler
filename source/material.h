// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include <memory>
#include <vector>
#include "gl_shader.h"
#include "resource_manager.h"
#include "string_utils.h"
#include "texture.h"

class material : public resource
{
public:
  material() = default;
  void set_textures(const strings& texture_names, resource_manager& rm);
  void set_shader(std::shared_ptr<gl_shader> shader);

  void use_on_gl_thread();

private:
  std::vector<std::shared_ptr<texture>> m_textures;
  std::shared_ptr<gl_shader> m_shader;
};

