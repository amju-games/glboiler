// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include "resource_manager.h"

void resource_manager::add_gl_resource(const std::string& name, std::shared_ptr<gl_resource> res)
{
  auto it = m_gl_res_map.find(name);

  if (it == m_gl_res_map.end())
  {
    m_gl_res_map[name] = res;

    // TODO add to a 'pending upload' set, then on the gl thread we upload any
    //  textures needing to be uploaded. 

    // Just for now. TODO
    res->upload_on_gl_thread();
  }
  else
  {
    log(msg() << "Resource already added: " << name);
  }
}

std::shared_ptr<texture> resource_manager::get_texture(const std::string& name, bool load_on_demand)
{
  auto it = m_gl_res_map.find(name);

  if (it == m_gl_res_map.end())
  {
    if (load_on_demand)
    {
      std::shared_ptr<texture> tex(new texture);
      tex->load(name); // name is filename for textures, we assume

      // Add to pending set for upload on gl thread
      m_to_upload.insert(tex);

      // TODO TEMP TEST
      tex->upload_on_gl_thread();

      m_gl_res_map[name] = tex;
      return tex;
    }

    log(msg() << "texture Resource does not exist: " << name);
    gl_boiler_stop;
    return nullptr;
  }
  else
  {
    return std::dynamic_pointer_cast<texture>(it->second);
  }
}

