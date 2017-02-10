// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include "bounding_vol.h"
#include "vec3.h"

class aabb : public bounding_vol
{
public:
  aabb() = default;
  aabb(const vec3& min, const vec3& max) : m_min(min), m_max(max) {}

  virtual cull_result calc_cull_result(const frustum& fr) const override; 

  vec3 get_min() const;
  vec3 get_max() const;

  // Calc union of this aabb and the other, i.e. a new box which encloses both.
  aabb union_with(const aabb& other);

  // Set extents if required to enclose p
  void set_if(const vec3& p);

private:
  vec3 m_min;
  vec3 m_max;
};

