// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include <memory>
#include "cull_result.h"
#include "frustum.h"
#include "object.h"

class bounding_vol : public object
{
public:
  virtual ~bounding_vol() {}

  virtual cull_result calc_cull_result(const frustum& fr) const
  {
    return cull_result::FRUSTUM_INSIDE_AND_OUTSIDE;
  }

  virtual void debug_render_on_gl_thread() const {}

  // Return new transformed bounding volume of same type
  virtual bounding_vol* transform_by(const mat4& m) const
  {
    return new bounding_vol(*this);
  }
};

