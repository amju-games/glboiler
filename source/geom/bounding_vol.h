// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include "cull_result.h"
#include "frustum.h"
#include "object.h"

class bounding_vol : public object
{
public:
  virtual ~bounding_vol() {}
  virtual cull_result calc_cull_result(const frustum& fr) const = 0;
};

