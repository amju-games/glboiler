// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include "resource_manager.h"

void resource_manager::add_gl_resource(const std::string& name, std::shared_ptr<gl_resource> res)
{
  auto it = m_gl_res_map.find(name);

  res->set_name(name);

  if (it == m_gl_res_map.end())
  {
    m_gl_res_map[name] = res;

    // Add to a 'pending upload' set, then on the gl thread we upload any
    //  textures needing to be uploaded. 
    m_to_upload.insert(res);
  }
  else
  {
    log(msg() << "Resource already added: " << name);
  }
}

void resource_manager::update_on_gl_thread()
{
  for (auto res : m_to_upload)
  {
    res->upload_on_gl_thread();
  }

  m_to_upload.clear();

  for (auto res : m_to_destroy)
  {
    res->destroy_on_gl_thread();
  }

  m_to_destroy.clear();
}

void resource_manager::report() const
{
}

void resource_manager::clear()
{

}

void resource_manager::reload_all()
{
  for (auto it : m_gl_res_map)
  {
    it.second->reload();

    m_to_upload.insert(it.second);
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

std::shared_ptr<gl_shader> resource_manager::get_shader(const std::string& name)
{
  auto it = m_gl_res_map.find(name);

  if (it == m_gl_res_map.end())
  {
    log(msg() << "texture Resource does not exist: " << name);
    gl_boiler_stop;
    return nullptr;
  }
  else
  {
    return std::dynamic_pointer_cast<gl_shader>(it->second);
  }
}


