// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include <string>
#include <memory>
#include <map>
#include "resource.h"
#include "texture.h"

class resource_manager
{
public:
  std::shared_ptr<texture> get_texture(const std::string& filename);

  void report() const;
  void clear();

  // TODO call clear at exit, so we don't assert that gl textures have been destroyed on the gl thread.
  // Argh, that won't be the gl thread though. Need to explicitly shut down res manager on the 
  //  gl thread.

private:
  using res_map = std::map<std::string, std::shared_ptr<texture>>;
  res_map m_res_map;
};

