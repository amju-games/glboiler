// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include "bounding_vol.h"
#include "vec3.h"

// * aabb *
// Axis-aligned bounding box, represented by two opposite corners, min and max.
class aabb : public bounding_vol
{
public:
  aabb() = default;
  aabb(const vec3& min, const vec3& max);

  virtual cull_result calc_cull_result(const frustum& fr) const override; 

  // * debug_render_on_gl_thread *
  // Draws an aabb, intended for debugging
  virtual void debug_render_on_gl_thread() const override;

  virtual aabb* transform_by(const mat4& m) const override;

  const vec3& get_min() const;
  const vec3& get_max() const;

  // Calc union of this aabb and the other, i.e. a new box which encloses both.
  aabb union_with(const aabb& other) const;

  // Set extents if required to enclose p
  void include(const vec3& p);

private:
  vec3 m_min;
  vec3 m_max;
};


