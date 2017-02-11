// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include "resource.h"

class gl_mesh : public gl_resource
{
public:
  // Not virtual, different resources have different load functions (e.g. shader)
  virtual bool load(const std::string& filename) = 0;

private:

};

