// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include <memory>
#include <vector>
#include "gl_shader.h"
#include "gl_texture.h"
#include "object.h"
#include "string_utils.h"

// * material *
// Not a resource, but we point to resources.
class material : public object
{
public:
  material();
  void set_texture(std::shared_ptr<gl_texture> tex, int active_texture_id);
  void set_shader(std::shared_ptr<gl_shader> shader);

  // Pass on to  the resources to which we point
  void use_on_gl_thread();

private:
  // Materials have zero or more textures, which are interpreted by the shader.
  // The position in the vector is the active texture ID.
  std::vector<std::shared_ptr<gl_texture>> m_textures;

  // Materials have one shader
  std::shared_ptr<gl_shader> m_shader;
};

