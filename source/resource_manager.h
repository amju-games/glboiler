// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include <map>
#include <memory>
#include <set>
#include <string>
#include "gl_mesh.h"
#include "gl_shader.h"
#include "gl_texture.h"
#include "resource.h"

class resource_manager
{
public:
  // If name is filename, we can load texture on demand, i.e. if not already added to res map.
  std::shared_ptr<gl_texture> get_texture(const std::string& name);

  // We can load shaders on demand if the filename for the two files is made from the
  //  resource name.
  std::shared_ptr<gl_shader> get_shader(const std::string& name);

  std::shared_ptr<gl_mesh> get_mesh(const std::string& name);

  std::shared_ptr<gl_resource> get_resource(const std::string& name);

  void add_gl_resource(const std::string& name, std::shared_ptr<gl_resource> res);

  void report() const;
  void clear();

  // TODO call clear at exit, so we don't assert that gl textures have been destroyed on the gl thread.
  // Argh, that won't be the gl thread though. Need to explicitly shut down res manager on the 
  //  gl thread.

  void update_on_gl_thread();

  // Reload all resources from disk
  void reload_all();

private:
  // TODO map of gl resources, and another of non-gl resources?
  // gl resources need special treatment so they are uploaded/destroyed on the gl thread.

  using gl_res_map = std::map<std::string, std::shared_ptr<gl_resource>>;
  gl_res_map m_gl_res_map;

  using pending_set = std::set<std::shared_ptr<gl_resource>>;
  pending_set m_to_upload;
  pending_set m_to_destroy;
};

