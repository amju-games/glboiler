// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include "obj_mesh.h"
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
  log(msg() << "Reloading all resources:");

  for (auto it : m_gl_res_map)
  {
    log(msg() << ".." << it.first);

    it.second->reload();

    m_to_upload.insert(it.second);
  }
}

std::shared_ptr<gl_texture> resource_manager::get_texture(const std::string& name)
{
  auto it = m_gl_res_map.find(name);

  if (it == m_gl_res_map.end())
  {
    std::shared_ptr<gl_texture> tex(new gl_texture);
    if (!tex->load(name)) // name is filename for textures, we assume
    {
      log(msg() << "Failed to load texture: " << name);
      gl_boiler_stop;
      return nullptr;
    }

    // Add to pending set for upload on gl thread
    m_to_upload.insert(tex);

    m_gl_res_map[name] = tex;
    return tex;
  }
  else
  {
    return std::dynamic_pointer_cast<gl_texture>(it->second);
  }
}

std::shared_ptr<gl_shader> resource_manager::get_shader(const std::string& name)
{
  auto it = m_gl_res_map.find(name);

  if (it == m_gl_res_map.end())
  {
    // Load shader. This depends on a strict location and filename for the 
    //  vertex and fragment shaders!
    std::shared_ptr<gl_shader> sh(new gl_shader);
    if (!sh->load("shaders/" + name + ".v.txt", "shaders/" + name + ".f.txt"))
    {
      log(msg() << "Failed to load shader: " << name);
      gl_boiler_stop;
      return nullptr;
    }

    // Add to pending set for upload on gl thread
    m_to_upload.insert(sh);

    m_gl_res_map[name] = sh;
    return sh;
  }
  else
  {
    return std::dynamic_pointer_cast<gl_shader>(it->second);
  }
}

std::shared_ptr<gl_mesh> resource_manager::get_mesh(const std::string& name)
{
  auto it = m_gl_res_map.find(name);

  if (it == m_gl_res_map.end())
  {
    // Load mesh
    std::shared_ptr<ObjMesh> mesh(new ObjMesh);
    if (!mesh->load(name, *this))
    {
      log(msg() << "Failed to load mesh: " << name);
      gl_boiler_stop;
      return nullptr;
    }

    // Add to pending set for upload on gl thread
    m_to_upload.insert(mesh);

    m_gl_res_map[name] = mesh;
    return mesh;
  }
  else
  {
    return std::dynamic_pointer_cast<gl_mesh>(it->second);
  }
}

std::shared_ptr<gl_resource> resource_manager::get_resource(const std::string& name)
{
  auto it = m_gl_res_map.find(name);

  if (it == m_gl_res_map.end())
  {
    log(msg() << "Mesh resource does not exist: " << name);
    gl_boiler_stop;
    return nullptr;
  }

  return it->second;
}


