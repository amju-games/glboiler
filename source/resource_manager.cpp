// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include "resource_manager.h"

std::shared_ptr<texture> resource_manager::get_texture(const std::string& filename)
{
  auto it = m_res_map.find(filename);

  if (it == m_res_map.end())
  {
    std::shared_ptr<texture> tex(new texture);
    if (!tex->load(filename))
    {
      assert(0);
      return nullptr;
    }
    m_res_map[filename] = tex;

    // TODO add to a 'pending upload' set, then on the gl thread we upload any
    //  textures needing to be uploaded. 

    // Just for now. TODO
    tex->upload_on_gl_thread();

    return tex;
  }
  else
  {
    return it->second;
  }
}

