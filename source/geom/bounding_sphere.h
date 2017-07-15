// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include "bounding_vol.h"

class bounding_sphere : public bounding_vol
{
public:
  bounding_sphere() : m_radius(1.f) {}
  bounding_sphere(const vec3& centre_, float radius_) : 
    m_centre(centre_), m_radius(radius_) {}

  virtual cull_result calc_cull_result(const frustum& fr) const override;

  virtual bounding_sphere* transform_by(const mat4& m) const override;

  virtual void debug_render_on_gl_thread() const override;

private:
  vec3 m_centre;
  float m_radius;
};
